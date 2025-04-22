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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRaceStarted);
	UPROPERTY() FOnRaceStarted onRaceStarted; 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRaceFinished,  AKart*, _winner);
	UPROPERTY() FOnRaceFinished onRaceFinish;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKartLapCompleted,  AKart*, _kart, int, _lapNumber);
	UPROPERTY() FOnKartLapCompleted onKartLapCompleted;



	UPROPERTY()TArray<ACheckPoint*> checkpoints;
	UPROPERTY()TArray<FKartRaceInfo> kartRaceInfos;
	UPROPERTY()int maxLaps = 3;
	bool raceStarted = false;

public:
	/*FORCEINLINE int GetTotalCheckpoints()const { return checkpoints.Num(); }
	FORCEINLINE TArray<ACheckPoint*> GetCheckpoints() { return checkpoints; }
	FORCEINLINE TArray<FKartRaceInfo> GetKartInfosRaces() { return kartRaceInfos; }
	FORCEINLINE int MaxLaps()const { return maxLaps; }*/

	FORCEINLINE FOnRaceStarted& OnRaceStarted() { return onRaceStarted; }
	FORCEINLINE FOnRaceFinished& OnRaceFinished() { return onRaceFinish; }
	FORCEINLINE FOnKartLapCompleted& OnKartLapCompleted() { return onKartLapCompleted; }

	TArray<ACheckPoint*> GetCheckpoints() const { return checkpoints; }
	int GetTotalCheckpoints() const { return checkpoints.Num(); }
	int GetMaxLaps() const { return maxLaps; }

public:
	/*void RegisterCheckpoint(ACheckPoint* _newCheckpoint);
	ACheckPoint* GetNextCheckpoint(AActor* _player, int _currentCheckpointIndex) const;
	bool IsGoingWrongWay(AActor* _player, int _currentCheckpointIndex) const;
	void RegisterKart(AKart* _newKart);
	void UpdateRaceProgress();
	AKart* GetLeader() const;
	TArray<AKart*> GetRaceRanking() const;*/

	void RegisterCheckpoint( ACheckPoint* _newCheckpoint);
	void RegisterKart(AKart* _newKart);
	void StartRace();
	void UpdateRaceProgress();
	ACheckPoint* GetNextCheckpoint(int _currentCheckpointIndex) const;
	AKart* GetLeader() const;
	TArray<AKart*> GetRaceRanking() const;
	int GetKartPlacement(AKart* _kart) const;
	
};
