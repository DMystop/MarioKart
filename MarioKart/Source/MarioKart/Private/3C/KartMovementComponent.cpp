// Fill out your copyright notice in the Description page of Project Settings.


#include "3C/KartMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UKartMovementComponent::UKartMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKartMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UKartMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Move(DeltaTime);
	// ...
}

void UKartMovementComponent::Accelerate(const FInputActionValue& _value)
{
	if (boostIsActivate || !canMove)return;
	currentSpeed += acceleration;

	currentSpeed = currentSpeed > maxSpeed ? maxSpeed : currentSpeed;

	//UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(acceleration)+"km/h");
	addVelocity = true;

}

void UKartMovementComponent::Rotate(const FInputActionValue& _value)
{
	float _inputRotation = _value.Get<float>();
	if (_inputRotation == 0 || currentSpeed == 0)return;
	float _rotationValue = _inputRotation * rotationSpeed * (1 - (currentSpeed / maxSpeed) + minRotation) * GetWorld()->DeltaTimeSeconds;
	UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(_rotationValue));
	APawn* _owner = Cast<APawn>(GetOwner());
	_owner->AddControllerYawInput(_rotationValue);

}

void UKartMovementComponent::Move(float DeltaTime)
{
	if (currentSpeed == 0 || !canMove)return;

	AActor* _owner = GetOwner();

	FVector _forward = _owner->GetActorLocation() + _owner->GetActorForwardVector() * currentSpeed;

	FVector _newPos = UKismetMathLibrary::VInterpTo_Constant(_owner->GetActorLocation(), _forward, DeltaTime, abs(currentSpeed));

	_owner->SetActorLocation(_newPos);
	//UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(currentSpeed) +"km/h");


	if (!addVelocity && !boostIsActivate)
		GoBackToNeutral();
	if (!_owner->HasAuthority())
		onMove.Broadcast(_owner, _owner->GetTransform());

}

void UKartMovementComponent::GoBackToNeutral()
{

	if (currentSpeed > 0)
	{
		currentSpeed -= deceleration;

		currentSpeed = currentSpeed < 0 ? 0 : currentSpeed;

	}
	else if (currentSpeed < 0)
	{
		currentSpeed += deceleration;

		currentSpeed = currentSpeed > 0 ? 0 : currentSpeed;
	}
}

void UKartMovementComponent::Brake(const FInputActionValue& _value)
{
	if (boostIsActivate || !canMove)
		return;

	currentSpeed -= acceleration;

	currentSpeed = currentSpeed < -maxSpeed ? -maxSpeed : currentSpeed;


	addVelocity = true;
}

void UKartMovementComponent::Boost(const FInputActionValue& _value)
{
	UKismetSystemLibrary::PrintString(this, "Boost");
	currentSpeed = maxSpeed + 50;
	FTimerManager& _timerManager = GetWorld()->GetTimerManager();

	if (_timerManager.IsTimerActive(boostTimer))
	{
		_timerManager.ClearTimer(boostTimer);
	}

	_timerManager.SetTimer(boostTimer, this, &UKartMovementComponent::ResetBoost, 5.0f, false);

	boostIsActivate = true;
}

void UKartMovementComponent::Boost(float _boost, float _time)
{

	currentSpeed = maxSpeed + _boost;
	FTimerManager& _timerManager = GetWorld()->GetTimerManager();

	if (_timerManager.IsTimerActive(boostTimer))
	{
		_timerManager.ClearTimer(boostTimer);
	}

	_timerManager.SetTimer(boostTimer, this, &UKartMovementComponent::ResetBoost, _time, false);

	boostIsActivate = true;
}

void UKartMovementComponent::SetMoveStun(bool _isStun)
{
	if (_isStun)
	{
		currentSpeed = 0;
		FTimerManager& _tmanager = GetWorld()->GetTimerManager();

		if (_tmanager.TimerExists(boostTimer))
		{
			_tmanager.ClearTimer(boostTimer);
		}
		boostIsActivate = false;
		addVelocity = false;
		canMove = false;
	}
	else
	{
		canMove = true;
	}
}


