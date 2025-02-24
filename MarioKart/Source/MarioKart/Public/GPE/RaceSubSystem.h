#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "RaceSubSystem.generated.h"

class ACheckPoint;
UCLASS()
class MARIOKART_API URaceSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY()TArray<ACheckPoint*> checkpoints;

public:
	void RegisterCheckpoint(ACheckPoint* _newCheckpoint);
	ACheckPoint* GetNextCheckpoint(AActor* _player, int _currentCheckpointIndex) const;
	bool IsGoingWrongWay(AActor* _player, int _currentCheckpointIndex) const;
	
};
