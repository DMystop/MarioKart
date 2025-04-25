// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kart.h"
#include <GPE/Item.h>
#include "KartPlayerController.generated.h"

class ACoin;
UCLASS()
class MARIOKART_API AKartPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<AKart> kart;
private:
	virtual void BeginPlay()override;
	UFUNCTION(Server, Reliable) void ServerRPC_ChangePosition(AActor* _actor, FTransform _newTransform);
	UFUNCTION(Server, Reliable) void ServerRPC_ChangeMesh(UStaticMeshComponent* _mesh, FTransform _newTransform);
	UFUNCTION(Server, Reliable) void ServerRPC_Spawnactor(TSubclassOf<AItem> _actor, AKart* _kart);
	UFUNCTION(Server, Reliable) void ServerRPC_SpawnCoinActor(TSubclassOf<ACoin> _coinToSpawn, const FVector& _spawnLocation, const FRotator& _spawnRotation, const bool _canRespawn, const bool _canRotate);
};
