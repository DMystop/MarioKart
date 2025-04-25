// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPE/Item.h"
#include "Coin.generated.h"

class URespawnComponent;
UCLASS()
class MARIOKART_API ACoin : public AItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)float rotationSpeed = 250.0f;
	UPROPERTY(EditAnywhere) bool canRotate = true;
	UPROPERTY(EditAnywhere) bool canRespawn = true;
	UPROPERTY(EditAnywhere) TObjectPtr<URespawnComponent> respawnComponent = nullptr;


public:
	FORCEINLINE void SetCanRotate(const bool _canRotate) { canRotate = _canRotate; }
	FORCEINLINE void SetCanRespawn(const bool _canRespawn) { canRespawn = _canRespawn; }

public:
	ACoin();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Use(AKart* _targetKart)override;
	void Rotate(float _delta);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void AddCoinToInventory(const int _coinQuantity, AKart* _targetKart);
};
