// Fill out your copyright notice in the Description page of Project Settings.


#include "3C/KartPlayerController.h"
#include "3C/KartMovementComponent.h"
#include "3C/InventoryComponent.h"
#include "3C/StunComponentComponent.h"
#include <Dashboard_HUD.h>
#include "GPE/Coin.h"
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
		UStunComponent* _stun = kart->GetStun();


		if(_movement)
			_movement->OnMove().AddDynamic(this, &AKartPlayerController::ServerRPC_ChangePosition);
			_movement->OnMeshMove().AddDynamic(this, &AKartPlayerController::ServerRPC_ChangeMesh);
		if (_inventory)
			_inventory->OnUse().AddDynamic(this, &AKartPlayerController::ServerRPC_Spawnactor);
		if (_stun)
			_stun->OnSpawnCoinActor().AddDynamic(this, &AKartPlayerController::ServerRPC_SpawnCoinActor);
	}

	//if (IsLocalController())
	//{
	//	ADashboard_HUD* HUD = Cast<ADashboard_HUD>(GetHUD());
	//	if (HUD)
	//	{
	//		HUD->InitDashboardWidget();
	//	}
	//}
}

void AKartPlayerController::ServerRPC_SpawnCoinActor_Implementation(TSubclassOf<ACoin> _coinToSpawn, const FVector& _spawnLocation, const FRotator& _spawnRotation, const bool _canRespawn, const bool _canRotate)
{
	ACoin* _coin = GetWorld()->SpawnActor<ACoin>(_coinToSpawn, _spawnLocation, _spawnRotation);
	_coin->SetCanRespawn(_canRespawn);
	_coin->SetCanRotate(_canRotate);
}

void AKartPlayerController::ServerRPC_ChangeMesh_Implementation(UStaticMeshComponent* _mesh, FTransform _newTransform)
{
	//UKismetSystemLibrary::PrintString(this, "hello");
	_mesh->SetRelativeTransform(_newTransform);
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
