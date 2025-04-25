#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MARIOKART_API URespawnComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float respawnTime = 5.0f;
	FTimerHandle respawnTimerHandle;
	ECollisionEnabled::Type originalCollision;

public:	
	URespawnComponent();

protected:
	virtual void BeginPlay() override;


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void HandleTaken();
	void Respawn();
		
};
