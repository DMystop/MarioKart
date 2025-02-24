#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostingZone.generated.h"

UCLASS()
class MARIOKART_API ABoostingZone : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoostingZone();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
