// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/Coin.h"
#include "3C/InventoryComponent.h"
#include <Dashboard_HUD.h>

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate(DeltaTime);
}

void ACoin::Use(AKart* _targetKart)
{
	AddCoinToInventory(1, _targetKart);
	Destroy();
}

void ACoin::Rotate(float _delta)
{
	FQuat _rotationDelta = FQuat(FRotator(0.f, rotationSpeed * _delta, 0.f));
	mesh->AddLocalRotation(_rotationDelta, false, nullptr, ETeleportType::None);
}

void ACoin::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor)return;

	AKart* _kart = Cast<AKart>(OtherActor);
	if (_kart)
	{
		AddCoinToInventory(1, _kart);
		Destroy();
	}
}

void ACoin::AddCoinToInventory(const int _coinQuantity, AKart* _targetKart)
{
	UInventoryComponent* _inventory = _targetKart->GetComponentByClass<UInventoryComponent>();
	if (!_inventory)return;
	_inventory->AddCoin(_coinQuantity);
}