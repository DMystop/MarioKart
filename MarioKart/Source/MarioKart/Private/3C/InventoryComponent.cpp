// Fill out your copyright notice in the Description page of Project Settings.


#include "3C/InventoryComponent.h"
#include "GPE/Item.h"
#include"Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(TSubclassOf<AItem> _item)
{
	if (items.Num() - 1 >= 2)return;
	items.Add(_item);

}

void UInventoryComponent::UseItem(const FInputActionValue& _value)
{
	UKismetSystemLibrary::PrintString(this, "Use");
	if (items.IsEmpty())return;
	AKart* _owner = Cast<AKart>(GetOwner());
	if (GetOwner()->HasAuthority())
	{
		AItem * _item = GetWorld()->SpawnActor<AItem>(items[0], GetOwner()->GetTransform());
		if(_item)
			_item->Use(_owner);

	}
	else
	{
		onUse.Broadcast(items[0],_owner);
	}
	items.RemoveAt(0);

}

