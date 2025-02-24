#include "GPE/Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);

}

void AItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
}



