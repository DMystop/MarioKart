#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Engine/TriggerBox.h"
#include "CheckPoint.generated.h"

UCLASS()
class MARIOKART_API ACheckPoint : public ATriggerBox
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)int checkpointIndex = 0;
	
public:
	ACheckPoint();

protected:
	virtual void BeginPlay() override;

private:
	void Init();
	UFUNCTION() void OnCheckPointOverlap(AActor* _overlappedActor, AActor* _otherActor);

};
