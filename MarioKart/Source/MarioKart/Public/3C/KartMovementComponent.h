// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include <Curves/CurveVector.h>
#include "KartMovementComponent.generated.h"

class AKart;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MARIOKART_API UKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMove, AActor*, _actor, FTransform, _currentTransform);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMeshMove, UStaticMeshComponent*, _mesh, FTransform, _currentTransform);
	UPROPERTY() FOnMove onMove;
	UPROPERTY() FOnMeshMove onMeshMove;
	// movement
	UPROPERTY(EditAnywhere)float acceleration = 10;
	UPROPERTY(EditAnywhere)float direction =  0;
	UPROPERTY(EditAnywhere)float driftDirection = 0;
	UPROPERTY(EditAnywhere)float currentSpeed = 0;
	UPROPERTY(EditAnywhere)float maxSpeed = 200;
	UPROPERTY(EditAnywhere)float deceleration = 2;
	UPROPERTY(EditAnywhere)float  minRotation = 0.4;
	UPROPERTY(EditAnywhere)float  rotationSpeed = 50;
	UPROPERTY(EditAnywhere)float  driftSpeed = 10;
	UPROPERTY(EditAnywhere)bool addVelocity = false;
	UPROPERTY(EditAnywhere)bool canMove = true;
	UPROPERTY(EditAnywhere)bool onRoad = true;
	UPROPERTY(EditAnywhere)bool isJump = false;
	UPROPERTY(EditAnywhere)FTimerHandle detectTimer ;
	UPROPERTY(EditAnywhere)TArray<TEnumAsByte<EObjectTypeQuery>> layers;
	UPROPERTY(EditAnywhere)TObjectPtr<AKart>kart;

	//Jump

	UPROPERTY(EditAnywhere)FTimerHandle jumpTimer ;
	UPROPERTY(EditAnywhere)TObjectPtr<UCurveVector> jumpCurve;
	UPROPERTY(EditAnywhere) float currentTime = 0;
	UPROPERTY(EditAnywhere) FVector start = FVector();


	//Boost
	UPROPERTY()FTimerHandle boostTimer;
	bool boostIsActivate = false;
	float driftBoost = 0;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)bool isDrifting = false;
public:
	FORCEINLINE void SetAddVelocity(const FInputActionValue& _value)
	{
		addVelocity = false;
		isDrifting = false;
	}

	FORCEINLINE void ResetBoost()
	{
		boostIsActivate = false;
	}

	FORCEINLINE FOnMove& OnMove()
	{
		return onMove;
	}
	FORCEINLINE FOnMeshMove& OnMeshMove()
	{
		return onMeshMove;
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
	void RotateDrift( float _value);
	void Move(float DeltaTime);
	void GoBackToNeutral();
	void Brake(const FInputActionValue& _value);
	void Boost(const FInputActionValue& _value);
	void Boost(float _boost, float _time);
	UFUNCTION()void SetMoveStun(bool _isStun);
	UFUNCTION()void DetectRoad();
	void DriftEnter(const FInputActionValue& _value);
	void DriftOut(const FInputActionValue& _value);
	void JumpToDrift(float _deltaTime);
	void UpdateDriftKart(float _deltaTime);
	void UpdateDriftBoost(float _deltaTime);
};
