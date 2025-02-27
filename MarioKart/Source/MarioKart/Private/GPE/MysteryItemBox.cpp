#include "GPE/MysteryItemBox.h"
#include "GPE/Item.h"
#include "GPE/Mushroom.h"
#include "GPE/Banana.h"
#include "GPE/Carapace.h"
#include "Kismet/KismetMathLibrary.h"

AMysteryItemBox::AMysteryItemBox()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
}

void AMysteryItemBox::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AMysteryItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Levitate(DeltaTime);
	Rotate(DeltaTime);

}

void AMysteryItemBox::Init()
{
	if (mushroomClass)
		availablesItems.Add(NewObject<AItem>(this, mushroomClass));
	if (bananaClass)
		availablesItems.Add(NewObject<AItem>(this, bananaClass));
	if (carapaceClass)
		availablesItems.Add(NewObject<AItem>(this, carapaceClass));
}

void AMysteryItemBox::Levitate(float _delta)
{
	FVector _loc = GetActorLocation();
	_loc.Z += FMath::Sin(runningTime * levitateSpeed) * levitateAmplitude * _delta;

	SetActorLocation(_loc);
	runningTime += _delta;
}

void AMysteryItemBox::Rotate(float _delta)
{
	FQuat _rotationDelta = FQuat(FRotator(0.f, rotationSpeed * _delta, 0.f));
	mesh->AddLocalRotation(_rotationDelta, false, nullptr, ETeleportType::None);
}



AItem* AMysteryItemBox::GiveRandomItem()
{
	if (!IsValidItemArray())return nullptr;

	int _count = availablesItems.Num() - 1;
	int _randomIndex = FMath::RandRange(0, _count);

	return availablesItems[_randomIndex];
}

void AMysteryItemBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor)return;

	//TODO Give the item to the inventory component
}

