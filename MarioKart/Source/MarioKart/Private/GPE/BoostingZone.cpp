#include "GPE/BoostingZone.h"

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

	//TODO Cast to player and boost
}

