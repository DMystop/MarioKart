#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.h"
#include "Goomba.generated.h"

class UBillboardComponent;
UCLASS()
class MARIOKART_API AGoomba : public AEnemy
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "Goomba") float moveSpeed = 100.0f;
	UPROPERTY(VisibleAnywhere, Category = "Goomba|Patrol") TObjectPtr<UBillboardComponent> patrolPointA;
	UPROPERTY(VisibleAnywhere, Category = "Goomba|Patrol") TObjectPtr<UBillboardComponent> patrolPointB;
	UPROPERTY(EditAnywhere, Category = "Goomba|Patrol")	float switchDistance = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Goomba") TObjectPtr<UStaticMeshComponent> goombaMesh;

	TArray<FVector> patrolPoints;
	int currentTargetIndex = 0;
public:
	AGoomba();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void MoveToTarget(float _deltaTime);
	void CheckSwitchTarget();
	void SwitchTarget();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void NotifyActorBeginOverlap(AActor* OtherActor);
	void Collision();

};