#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "Carapace.generated.h"

class AKart;
UCLASS()
class MARIOKART_API ACarapace : public AItem
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)int maxBounces = 3;
	UPROPERTY(EditAnywhere)float rotationSpeed = 500.0f;
	UPROPERTY(EditAnywhere)float moveSpeed = 500.0f;
	UPROPERTY(EditAnywhere) int dir = 1;
	int currentBounces = 0;
	//bool canMove = false;
	
public:	
	ACarapace();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Use(AKart* _targetKart)override;
private:
	void Rotate(float _delta);
	void Move(float _delta);
	void Collision();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

};
