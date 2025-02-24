// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KartPawn.generated.h"

class ACheckPoint;
UCLASS()
class MARIOKART_API AKartPawn : public APawn
{
	GENERATED_BODY()

protected:
//	// Index du dernier checkpoint atteint
//	int currentCheckpointIndex = 0;
//
//public:
//	// Met à jour le checkpoint actuel
//	void SetCurrentCheckpoint(ACheckPoint* Checkpoint);

public:
	// Sets default values for this pawn's properties
	AKartPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
