// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kart.generated.h"

class UKartMovementComponent;
class UInventoryComponent;
class UStunComponent;
USTRUCT()
struct FInput
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)TObjectPtr<UInputMappingContext>mappingContext;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>accelerateAction;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>turnAction;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>brakeAction;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>boostAction;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>useAction;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>shootBehindAction;
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>stunAction;

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
	UPROPERTY(EditAnywhere)TObjectPtr<UInventoryComponent>inventory;
	UPROPERTY(EditAnywhere)bool shootBehind = false;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)TObjectPtr<UStunComponent>stunComponent;
public:
	FORCEINLINE TObjectPtr<UKartMovementComponent> GetMovement() { return movement; }
	FORCEINLINE TObjectPtr<UInventoryComponent> GetInventory() { return inventory; }
	FORCEINLINE bool GetShootDirection() const { return shootBehind; }

public:
	// Sets default values for this pawn's properties
	AKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Bind();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitInput();
public:
	void ToggleShootDirection(const FInputActionValue& _value);


};
