// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kart.generated.h"

class UKartMovementComponent;
USTRUCT()
struct FInput
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)TObjectPtr<UInputMappingContext>mappingContext;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>accelerateAction;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>turnAction;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>brakeAction;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>boostAction;

};

UCLASS()
class MARIOKART_API AKart : public APawn
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)TObjectPtr<USpringArmComponent>arm;
	UPROPERTY(EditAnywhere)TObjectPtr<UCameraComponent>camera;
	UPROPERTY(EditAnywhere)TObjectPtr<UStaticMeshComponent>mesh;

	UPROPERTY(EditAnywhere)FInput input;
	UPROPERTY(EditAnywhere)TObjectPtr<UKartMovementComponent>movement;
	

public:
	// Sets default values for this pawn's properties
	AKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitInput();
public:

};
