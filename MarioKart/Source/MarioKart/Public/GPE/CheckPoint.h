#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "CheckPoint.generated.h"

UCLASS()
class MARIOKART_API ACheckPoint : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)TObjectPtr<UBoxComponent>collisionBox = nullptr;
	
public:
	ACheckPoint();

protected:
	virtual void BeginPlay() override;

private:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void Init();

};
