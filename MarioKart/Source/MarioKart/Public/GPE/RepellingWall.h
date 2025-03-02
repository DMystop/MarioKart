#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RepellingWall.generated.h"

UCLASS()
class MARIOKART_API ARepellingWall : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)float repelDistance = 500.0f;
	UPROPERTY(EditAnywhere)float repelSpeed = 2.0f;
	APawn* repelledPawn = nullptr;
	FVector repelDirection;
	FVector startLocation;
	FVector targetLocation;
	float repelProgress = 0.0f;
	
public:	
	ARepellingWall();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void RepelPawn(float _delta);

};
