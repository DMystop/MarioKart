// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <InputActionValue.h>
#include "InventoryComponent.generated.h"

class AItem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARIOKART_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUse, TSubclassOf<AItem>, _item, AKart*, _kart);
	UPROPERTY() FOnUse onUse;
	UPROPERTY(EditAnywhere)TArray<TSubclassOf<AItem>> items;
	UPROPERTY(EditAnywhere)int maxCount = 2;
	
public:
	FORCEINLINE FOnUse& OnUse()
	{
		return onUse;
	}
public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddItem(TSubclassOf<AItem> _item);
	void UseItem(const FInputActionValue& _value);
		
};
