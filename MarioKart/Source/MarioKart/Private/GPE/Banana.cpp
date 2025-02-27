#include "GPE/Banana.h"

ABanana::ABanana()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
}

void ABanana::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABanana::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABanana::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor)return;

	//TODO Player
}

