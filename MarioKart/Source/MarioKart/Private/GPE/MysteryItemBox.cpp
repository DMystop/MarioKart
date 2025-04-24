#include "GPE/MysteryItemBox.h"
#include "GPE/Item.h"
#include "GPE/Mushroom.h"
#include "GPE/Banana.h"
#include "GPE/Carapace.h"
#include "Kismet/KismetMathLibrary.h"
#include"Kismet/KismetSystemLibrary.h"
#include "3C/Kart.h"
#include "3C/InventoryComponent.h"
#include "GPE/ItemBoxSubSystem.h"
#include <Kismet/KismetSystemLibrary.h>

AMysteryItemBox::AMysteryItemBox()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
	
	bReplicates = true;
	mesh->SetIsReplicated(true);
	SetReplicates(true);
}

void AMysteryItemBox::BeginPlay()
{
	Super::BeginPlay();
	// Init();
}

void AMysteryItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Levitate(DeltaTime);
	Rotate(DeltaTime);

}

void AMysteryItemBox::Init()
{
	/*if (mushroomClass)
		availablesItems.Add(NewObject<AItem>(this, mushroomClass));
	if (bananaClass)
		availablesItems.Add(NewObject<AItem>(this, bananaClass));
	if (carapaceClass)
		availablesItems.Add(NewObject<AItem>(this, carapaceClass));*/


	//availablesItems.Add(mushroomClass);
	//availablesItems.Add(bananaClass);
	//availablesItems.Add(carapaceClass);

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



TSubclassOf<AItem> AMysteryItemBox::GiveRandomItem()
{
	/*if (!IsValidItemArray())return nullptr;

	int _count = availablesItems.Num() - 1;
	int _randomIndex = FMath::RandRange(0, _count);

	return availablesItems[_randomIndex];*/


	if (!IsValidItemArray())
	{
		UKismetSystemLibrary::PrintString(this, "Salut");
		return nullptr;
	}

	int _count = availablesItems.Num() - 1;
	UKismetSystemLibrary::PrintString(this, "Count => " + FString::FromInt(_count), true, true, FLinearColor::Red, 10.0f);
	int _randomIndex = FMath::RandRange(0, _count);
	UKismetSystemLibrary::PrintString(this, "Random Index => " + FString::FromInt(_randomIndex), true, true, FLinearColor::Red, 10.0f);


	return availablesItems[_randomIndex];
}

void AMysteryItemBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor)return;

	AKart* _kart = Cast<AKart>(OtherActor);
	if (_kart)
	{
		UInventoryComponent* _inventory = _kart->GetComponentByClass<UInventoryComponent>();
		if (!_inventory)return;
		_inventory->AddItem(GiveRandomItem());
		//Destroy();
		HandleTaken();
	}
	
}

void AMysteryItemBox::HandleTaken()
{
	mesh->SetVisibility(false);
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorldTimerManager().SetTimer(respawnTimerHandle, this, &AMysteryItemBox::Respawn, respawnTime, false);
}

void AMysteryItemBox::Respawn()
{
	mesh->SetVisibility(true);
	mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}


