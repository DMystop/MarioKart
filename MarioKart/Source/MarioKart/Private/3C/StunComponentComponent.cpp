// Fill out your copyright notice in the Description page of Project Settings.

#include"3C/StunComponentComponent.h"


#include <Kismet/KismetSystemLibrary.h>

// Sets default values for this component's properties
UStunComponent::UStunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UStunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStunComponent::Stun()
{
	if (isStun)return;

	FTimerManager& _tmanager = GetWorld()->GetTimerManager();

	if (_tmanager.TimerExists(stun))
	{
		_tmanager.ClearTimer(stun);
	}


	FTimerDelegate _delegate;
	_delegate.BindLambda([&]() {

		isStun = false;
		onStun.Broadcast(isStun);
		});
	_tmanager.SetTimer(stun, _delegate, timeStun, true);

	isStun = true;
	onStun.Broadcast(isStun);
	UKismetSystemLibrary::PrintString(this, "StunComponent");

}

void UStunComponent::StunAction(const FInputActionValue& _value)
{
	Stun();
}

