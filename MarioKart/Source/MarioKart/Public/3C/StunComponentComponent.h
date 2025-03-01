// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <InputActionValue.h>
#include "StunComponentComponent.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MARIOKART_API UStunComponent : public UActorComponent
{

	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStun, bool, _isStun);
	UPROPERTY() FOnStun onStun;

	UPROPERTY()FTimerHandle stun;
	UPROPERTY()bool isStun = false;
	UPROPERTY()float timeStun = 3.0f;

public:
	FORCEINLINE FOnStun& OnStun()
	{
		return  onStun;
	}
public:
	// Sets default values for this component's properties
	UStunComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable) void Stun();
	void StunAction(const FInputActionValue& _value);

};
