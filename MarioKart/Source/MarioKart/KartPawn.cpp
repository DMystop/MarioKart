// Fill out your copyright notice in the Description page of Project Settings.


#include "KartPawn.h"
#include "GPE/CheckPoint.h"
#include "GPE/RaceSubSystem.h"

// Sets default values
AKartPawn::AKartPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKartPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKartPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKartPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//void AKartPawn::SetCurrentCheckpoint(ACheckPoint* _checkpoint)
//{
//	if (!_checkpoint || !GetGameInstance()) return;
//
//	URaceSubsystem* _raceSubsystem = GetGameInstance()->GetSubsystem<URaceSubsystem>();
//	if (!_raceSubsystem) return;
//
//	// Trouver l'index du checkpoint actuel
//	int _newIndex = _raceSubsystem->GetCheckpoints().Find(Checkpoint);
//	if (_newIndex != INDEX_NONE)
//	{
//		currentCheckpointIndex = _newIndex;
//	}
//}

