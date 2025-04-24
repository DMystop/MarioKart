// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GPE/RaceSubSystem.h"
#include "Net/UnrealNetwork.h"
#include "Kart.generated.h"

class UKartMovementComponent;
class UInventoryComponent;
class UStunComponent;
class ACheckPoint;
class URaceSubSystem;
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
	UPROPERTY(EditAnywhere)TObjectPtr<UInputAction>driftAction;

};

UCLASS()
class MARIOKART_API AKart : public APawn

{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLapCompleted, class AKart*, _kart);
	UPROPERTY() FOnLapCompleted onLapCompleted; 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRaceFinished, class AKart*, _kart);
	UPROPERTY() FOnRaceFinished onRaceFinished;

	UPROPERTY(EditAnywhere)TObjectPtr<USpringArmComponent>arm;
	UPROPERTY(EditAnywhere)TObjectPtr<UCameraComponent>camera;
	UPROPERTY(EditAnywhere)TObjectPtr<UStaticMeshComponent>mesh;

	UPROPERTY(EditAnywhere)FInput input;
	UPROPERTY(EditAnywhere)TObjectPtr<UKartMovementComponent>movement;
	UPROPERTY(EditAnywhere)TObjectPtr<UInventoryComponent>inventory;
	UPROPERTY(EditAnywhere)bool shootBehind = false;
	UPROPERTY(ReplicatedUsing = OnRep_CurrentCheckpoint) int currentCheckPointIndex = 0;
	UPROPERTY(ReplicatedUsing = OnRep_CurrentLap) int currentLap = 0;
	UPROPERTY() int maxLap = 3;
	UPROPERTY() int lapsCompleted = 0;
	UPROPERTY() URaceSubSystem* raceSubSystem;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)TObjectPtr<UStunComponent>stunComponent;
public:
	FORCEINLINE TObjectPtr<UKartMovementComponent> GetMovement() { return movement; }
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetMesh() { return mesh; }
	FORCEINLINE TObjectPtr<UInventoryComponent> GetInventory() { return inventory; }
	FORCEINLINE bool GetShootDirection() const { return shootBehind; }

	FORCEINLINE FOnLapCompleted& OnLapCompleted() { return onLapCompleted; }
	FORCEINLINE FOnRaceFinished& OnRaceFinished() { return onRaceFinished; }
	FORCEINLINE int GetLapCompleted() { return currentLap; }
	FORCEINLINE int GetCurrentCheckpoint() { return currentCheckPointIndex; }

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
	void Init();
public:
	void ToggleShootDirection(const FInputActionValue& _value);
	void SetCurrentCheckpoint(int _checkpoint);
	UFUNCTION(Server, Reliable, WithValidation)void Server_ValidateCheckpoint(ACheckPoint* _checkpoint);
	bool Server_ValidateCheckpoint_Validate(ACheckPoint* _checkpoint);
	void ValidateCheckpoint(ACheckPoint* _checkPoint);
	UFUNCTION()void OnRep_CurrentCheckpoint();
	UFUNCTION()void OnRep_CurrentLap();


};
