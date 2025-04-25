// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <InputActionValue.h>
#include "StunComponentComponent.generated.h"


class ACoin;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MARIOKART_API UStunComponent : public UActorComponent
{

	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStun, bool, _isStun);
	UPROPERTY() FOnStun onStun;

	UPROPERTY(EditAnywhere, Category = "Coin Drop")	TSubclassOf<ACoin> coinToSpawn;
	UPROPERTY()FTimerHandle stun;
	UPROPERTY()float timeStun = 3.0f;

protected:
	UPROPERTY(BlueprintReadOnly)bool isStun = false;


public:
	FORCEINLINE FOnStun& OnStun()
	{
		return  onStun;
	}
public:
	UStunComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable) void Stun();
	void LoseAndDropCoins();
	void StunAction(const FInputActionValue& _value);

};
