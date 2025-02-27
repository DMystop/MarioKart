#include "GPE/BoostingZone.h"
#include "3C/Kart.h"
#include "3C/KartMovementComponent.h"

ABoostingZone::ABoostingZone()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
}

void ABoostingZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoostingZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoostingZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor)return;

	AKart* _kart = Cast < AKart>(OtherActor);
	if (!_kart)return;
	UKartMovementComponent* _movement = _kart->GetComponentByClass<UKartMovementComponent>();
	if (!_movement)return;
	_movement->Boost(boostValue, boostTime);
}

