#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "RaceSubSystem.generated.h"

class ACheckPoint;
class AKart;

USTRUCT()
struct FKartRaceInfo
{
	GENERATED_BODY()

	TObjectPtr<AKart> kart;
	int currentLap = 0;
	int currentCheckpoint = 0;
	float distanceToNextCheckpoint = 0.0f;
};

UCLASS()
class MARIOKART_API URaceSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY()TArray<ACheckPoint*> checkpoints;
	UPROPERTY()TArray<FKartRaceInfo> kartRaceInfos;
	UPROPERTY()int maxLaps = 3;

public:
	void RegisterCheckpoint(ACheckPoint* _newCheckpoint);
	ACheckPoint* GetNextCheckpoint(AActor* _player, int _currentCheckpointIndex) const;
	bool IsGoingWrongWay(AActor* _player, int _currentCheckpointIndex) const;
	void RegisterKart(AKart* _newKart);
	void UpdateRaceProgress();
	AKart* GetLeader() const;
	
};
