// Fill out your copyright notice in the Description page of Project Settings.


#include "3C/KartMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include"3C/Kart.h"

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

	GetWorld()->GetTimerManager().SetTimer(detectTimer,this, &UKartMovementComponent::DetectRoad, 0.5f, true);
	
	kart = Cast<AKart>(GetOwner());
	// ...

}


// Called every frame
void UKartMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Move(DeltaTime);
	if (isJump)
	{
		JumpToDrift(DeltaTime);
	}
	UpdateDriftKart(DeltaTime);
	if (isDrifting)
	{
		RotateDrift(driftDirection);
		UpdateDriftBoost(DeltaTime);
	}
	else
	{
		driftBoost = 0;
	}
	// ...
}

void UKartMovementComponent::Accelerate(const FInputActionValue& _value)
{
	if (boostIsActivate || !canMove)return;
	currentSpeed += acceleration;

	if (onRoad)
	{
		float _maxSpeedCoin = maxSpeed + coinCount * (maxSpeed * coinBoostfactor);
		currentSpeed = currentSpeed > _maxSpeedCoin ? _maxSpeedCoin : currentSpeed;

	}
	else
	{
		currentSpeed = currentSpeed > maxSpeed/2 ? maxSpeed/2 : currentSpeed;
		//UKismetSystemLibrary::PrintString(this, "HorsPiste");
	}

	//UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(acceleration)+"km/h");
	addVelocity = true;

}

void UKartMovementComponent::Rotate(const FInputActionValue& _value)
{
	float _inputRotation = _value.Get<float>();
	direction = _inputRotation;
	if (_inputRotation == 0 || currentSpeed == 0)return;
	float _speed = isDrifting ? rotationSpeed / 2 : rotationSpeed;
	float _rotationValue = _inputRotation * _speed * (1 - (currentSpeed / maxSpeed) + minRotation) * GetWorld()->DeltaTimeSeconds;
	//UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(_rotationValue));
	APawn* _owner = Cast<APawn>(GetOwner());
	_owner->AddControllerYawInput(_rotationValue);

}

void UKartMovementComponent::RotateDrift(float _value)
{
	
	
	if (currentSpeed == 0)return;

	float _rotationValue = _value * driftSpeed * (1 - (currentSpeed / maxSpeed) + minRotation) * GetWorld()->DeltaTimeSeconds;
	//UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(_rotationValue));
	APawn* _owner = Cast<APawn>(GetOwner());
	_owner->AddControllerYawInput(_rotationValue);
}

void UKartMovementComponent::Move(float DeltaTime)
{
	if (currentSpeed == 0 || !canMove)return;

	AActor* _owner = GetOwner();

	FVector _forward = _owner->GetActorLocation() + _owner->GetActorForwardVector() * currentSpeed;

	if (isDrifting)
	{
		_forward += driftDirection * _owner->GetActorRightVector()*currentSpeed/2;
	}
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
		isDrifting = false;
	}
	else
	{
		canMove = true;
	}
}

void UKartMovementComponent::DetectRoad()
{
	TArray<AActor*> _toIgnore;
	AActor* _owner = GetOwner();
	TArray<FHitResult> _result = TArray<FHitResult>();
	onRoad=UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(), _owner->GetActorLocation(), _owner->GetActorLocation()+FVector::DownVector * 3000, layers, false, _toIgnore, EDrawDebugTrace::ForDuration, _result,true);

	if (!onRoad)
		isDrifting = false;
}

void UKartMovementComponent::DriftEnter(const FInputActionValue& _value)
{
	if (!isJump)
	{
	start = kart->GetMesh()->GetRelativeLocation();
	currentTime = 0;
	isJump = true;

	}
	if (direction == 0||!addVelocity||!onRoad)return;
	isDrifting = true;
	driftDirection = direction;
	//UKismetSystemLibrary::PrintString(this, "this");
	//GetWorld()->GetTimerManager().SetTimer(jumpTimer, this,&UKartMovementComponent::JumpToDrift, 0.1f,true);
}

void UKartMovementComponent::DriftOut(const FInputActionValue& _value)
{

	if (isDrifting)
	{
		if (driftBoost > 3.f)
		{
			Boost(100, 2);
			UKismetSystemLibrary::PrintString(this, "Gros");
		}

		else if (driftBoost > 1.5f)
		{
			UKismetSystemLibrary::PrintString(this, "Petit");
			Boost(50, 1);
		}

		driftBoost = 0;
		
	}
	isDrifting = false;
}

void UKartMovementComponent::JumpToDrift(float _deltaTime)
{
	currentTime += _deltaTime;

	FVector _newLoc = start + jumpCurve->GetVectorValue(currentTime);
	kart->GetMesh()->SetRelativeLocation(_newLoc);
	if (currentTime > jumpCurve->FloatCurves->GetLastKey().Time)
		/*GetWorld()->GetTimerManager().ClearTimer(jumpTimer)*/
		isJump=false;

	if (!kart->HasAuthority())
		onMeshMove.Broadcast(kart->GetMesh(), kart->GetMesh()->GetRelativeTransform());
}

void UKartMovementComponent::UpdateDriftKart(float _deltaTime)
{
	if (!kart || !kart->GetMesh())return;

	float _speed = isDrifting ? 10.f : 50.f;

	float _yawOffset = isDrifting ? driftDirection * 10.f : 0;

	FRotator _currentRot = kart->GetMesh()->GetRelativeRotation();
	FRotator _targetRot = FRotator(_currentRot.Pitch, _yawOffset, _currentRot.Roll);

	FRotator _rewRotation = FMath::RInterpConstantTo(_currentRot, _targetRot, _deltaTime, _speed);
	kart->GetMesh()->SetRelativeRotation(_rewRotation);

	
	if (!kart->HasAuthority())
		onMeshMove.Broadcast(kart->GetMesh(), kart->GetMesh()->GetRelativeTransform());
}

void UKartMovementComponent::UpdateDriftBoost(float _deltaTime)
{
	driftBoost += _deltaTime;
}

void UKartMovementComponent::UpdateCoinCount(float _count)
{
	coinCount = _count;
}


