#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Engine/TriggerBox.h"
#include "CheckPoint.generated.h"

UCLASS()
class MARIOKART_API ACheckPoint : public ATriggerBox
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCheckpointValidated, class AKart*, _kart, class ACheckPoint*, _checkPoint);
	UPROPERTY() FOnCheckpointValidated onCheckpointValidated;

	UPROPERTY(EditAnywhere)int checkpointIndex = 0;
	UPROPERTY(EditAnywhere)ACheckPoint* nextCheckpoint;

public:
	FORCEINLINE FOnCheckpointValidated& OnCheckpointValidated() {return onCheckpointValidated;}
	FORCEINLINE ACheckPoint* GetNextCheckpoint() const { return nextCheckpoint; }
	FORCEINLINE int GetCheckpointIndex() const { return checkpointIndex; }
	
public:
	ACheckPoint();

protected:
	virtual void BeginPlay() override;

private:
	void Init();
	UFUNCTION() void OnCheckPointOverlap(AActor* _overlappedActor, AActor* _otherActor);

};
