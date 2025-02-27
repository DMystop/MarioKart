// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "KartMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARIOKART_API UKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()
	// movement
	UPROPERTY(EditAnywhere)float acceleration=10;
	UPROPERTY(EditAnywhere)float currentSpeed=0;
	UPROPERTY(EditAnywhere)float maxSpeed=200;
	UPROPERTY(EditAnywhere)float deceleration=2;
	UPROPERTY(EditAnywhere)float  minRotation=0.4;
	UPROPERTY(EditAnywhere)float  rotationSpeed=50;
	UPROPERTY(EditAnywhere)bool addVelocity = false;

	//Boost
	UPROPERTY()FTimerHandle boostTimer;
	bool boostIsActivate = false;

public :
	FORCEINLINE void SetAddVelocity(const FInputActionValue& _value)
	{
		addVelocity = false;
	}
	
	FORCEINLINE void ResetBoost()
	{
		boostIsActivate = false;
	}
public:	
	// Sets default values for this component's properties
	UKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	

	void Accelerate(const FInputActionValue& _value);
	void Rotate(const FInputActionValue& _value);
	void Move(float DeltaTime);
	void GoBackToNeutral();
	void Brake(const FInputActionValue& _value);
	void Boost(const FInputActionValue& _value);
	void Boost(float _boost ,float _time);
		
};
