#include "GPE/Mushroom.h"
#include "3C/KartMovementComponent.h"

AMushroom::AMushroom()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = nullptr;
}

void AMushroom::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMushroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMushroom::Use(AKart* _targetKart)
{
	if (!_targetKart)return;
	UKartMovementComponent* _movement = _targetKart->GetComponentByClass<UKartMovementComponent>();
	if (!_movement)return;
	_movement->Boost(boostValue, boostTime);
}

