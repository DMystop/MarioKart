// Fill out your copyright notice in the Description page of Project Settings.

#include"3C/StunComponentComponent.h"
#include <3C/Kart.h>
#include "3C/InventoryComponent.h"
#include <GPE/Coin.h>
#include <3C/KartPlayerController.h>
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

//void UStunComponent::Stun()
//{
//	if (isStun)return;
//
//	FTimerManager& _tmanager = GetWorld()->GetTimerManager();
//
//	if (_tmanager.TimerExists(stun))
//	{
//		_tmanager.ClearTimer(stun);
//	}
//
//
//	FTimerDelegate _delegate;
//	_delegate.BindLambda([&]() {
//
//		isStun = false;
//		onStun.Broadcast(isStun);
//		});
//	_tmanager.SetTimer(stun, _delegate, timeStun, true);
//
//	isStun = true;
//	onStun.Broadcast(isStun);
//	UKismetSystemLibrary::PrintString(this, "StunComponent");
//
//}

void UStunComponent::Stun()
{
	if (isStun) return;

	LoseAndDropCoins();

	FTimerManager& _tmanager = GetWorld()->GetTimerManager();
	if (_tmanager.TimerExists(stun))
	{
		_tmanager.ClearTimer(stun);
	}

	FTimerDelegate _delegate;
	_delegate.BindLambda([&]()
		{
			isStun = false;
			onStun.Broadcast(isStun);
		});
	_tmanager.SetTimer(stun, _delegate, timeStun, true);

	isStun = true;
	onStun.Broadcast(isStun);
	UKismetSystemLibrary::PrintString(this, "StunComponent");
}

void UStunComponent::LoseAndDropCoins()
{
	AKart* _ownerKart = Cast<AKart>(GetOwner());
	if (_ownerKart)
	{
		UInventoryComponent* _inventory = _ownerKart->GetComponentByClass<UInventoryComponent>();
		if (_inventory && _inventory->GetCoinCount() >= 3)
		{
			_inventory->AddCoin(-3);

			if (coinToSpawn)
			{
				const FVector _center = _ownerKart->GetActorLocation();
				const float _radius = 200.f;
				const int _coinCount = 3;

				for (int i = 0; i < _coinCount; ++i)
				{
					float _angle = (2 * PI / _coinCount) * i;
					FVector _offset = FVector(FMath::Cos(_angle), FMath::Sin(_angle), 0.f) * _radius;
					FVector _spawnLocation = _center + _offset;
					FRotator _spawnRotation = FRotator::ZeroRotator;

					AKartPlayerController* _playerController = Cast<AKartPlayerController>(Cast<APawn>(GetOwner())->GetController());
					onSpawnCoinActor.Broadcast(coinToSpawn, _spawnLocation, _spawnRotation, false, false);
					// _playerController->ServerRPC_SpawnCoinActor(coinToSpawn, _spawnLocation, _spawnRotation, false, false);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("coinToSpawn is not set in StunComponent."));
			}
		}
	}
}



void UStunComponent::StunAction(const FInputActionValue& _value)
{
	Stun();
}

