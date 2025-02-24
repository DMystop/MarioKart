#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "Carapace.generated.h"

UCLASS()
class MARIOKART_API ACarapace : public AItem
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)TObjectPtr<UProjectileMovementComponent> movement = nullptr;
	UPROPERTY(EditAnywhere)int maxBounces = 3;
	UPROPERTY(EditAnywhere)float rotationSpeed = 360.0f;
	int currentBounces = 0;
	
public:	
	ACarapace();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Rotate(float _delta);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

};
