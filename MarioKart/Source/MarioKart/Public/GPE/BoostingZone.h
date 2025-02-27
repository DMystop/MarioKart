#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostingZone.generated.h"

UCLASS()
class MARIOKART_API ABoostingZone : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere) float boostValue = 200.0f;
	UPROPERTY(EditAnywhere) float boostTime = 3.0f;
	
public:	
	ABoostingZone();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
