// Fill out your copyright notice in the Description page of Project Settings.


#include "3C/KartPlayerController.h"
#include "3C/KartMovementComponent.h"
#include "3C/InventoryComponent.h"
#include <Kismet/KismetSystemLibrary.h>

void AKartPlayerController::BeginPlay()
{
	Super::BeginPlay();

	kart = Cast<AKart>(GetPawn());
	if (kart)
	{
	UKismetSystemLibrary::PrintString(this, "Bind");
		UKartMovementComponent* _movement = kart->GetMovement();
		UInventoryComponent* _inventory = kart->GetInventory();


		if(_movement)
			_movement->OnMove().AddDynamic(this, &AKartPlayerController::ServerRPC_ChangePosition);
		if (_inventory)
			_inventory->OnUse().AddDynamic(this, &AKartPlayerController::ServerRPC_Spawnactor);
	}
}

void AKartPlayerController::ServerRPC_Spawnactor_Implementation(TSubclassOf<AItem> _actor, AKart* _kart)
{
	AItem* _item = GetWorld()->SpawnActor<AItem>(_actor, _kart->GetTransform());
	if (_item)
		_item->Use(_kart);
}

void AKartPlayerController::ServerRPC_ChangePosition_Implementation(AActor* _actor,FTransform _newTransform)
{
	//UKismetSystemLibrary::PrintString(this, "coucou");

	
	_actor->SetActorTransform(_newTransform);
}
