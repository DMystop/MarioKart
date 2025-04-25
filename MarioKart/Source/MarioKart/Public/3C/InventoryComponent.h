#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <InputActionValue.h>
#include "InventoryComponent.generated.h"

class AItem;
class UDashboardWidget;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MARIOKART_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUse, TSubclassOf<AItem>, _item, AKart*, _kart);
	UPROPERTY() FOnUse onUse;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FonCoinChange,float,_count);
	UPROPERTY() FonCoinChange onCoinChange;

	UPROPERTY(EditAnywhere)TArray<TSubclassOf<AItem>> items;
	UPROPERTY(EditAnywhere)int maxCount = 2;
	UPROPERTY(EditAnywhere) bool canUse = true;
	UPROPERTY(EditAnywhere) int maxCoinCount = 10;
	UPROPERTY(EditAnywhere) int coinCount = 0;
public:
	FORCEINLINE FOnUse& OnUse()
	{
		return onUse;
	}
	FORCEINLINE FonCoinChange& OnCoinChange()
	{
		return onCoinChange;
	}
	FORCEINLINE int GetCoinCount() { return coinCount; }
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
	UFUNCTION() void SetCanUseOnStun(bool _isStun);
	UDashboardWidget* GetDashboardWidget() const;
	void UpdateItemDashboard();
	void UpdateCoinDashboard();
	void AddCoin(const int _count);
};