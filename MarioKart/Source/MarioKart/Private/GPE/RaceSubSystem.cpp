#include "GPE/RaceSubSystem.h"
#include "GPE/CheckPoint.h"
#include "3C/Kart.h"
#include "DashboardWidget.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Dashboard_HUD.h>

void URaceSubSystem::RegisterCheckpoint(ACheckPoint* _newCheckpoint)
{
	if (_newCheckpoint)
	{
		
		checkpoints.Add(_newCheckpoint);
	}
}

void URaceSubSystem::RegisterKart(AKart* _newKart)
{
	if (_newKart)
	{
		FKartRaceInfo _newKartInfo;
		_newKartInfo.kart = _newKart;
		kartRaceInfos.Add(_newKartInfo);
	}
}

void URaceSubSystem::StartRace()
{
	if (raceStarted)
		return;

	raceStarted = true;
	onRaceStarted.Broadcast();

	UKismetSystemLibrary::PrintString(this, "Race Started !", true, true, FLinearColor::Red, 10.0f);
}

void URaceSubSystem::UpdateRaceProgress()
{
	if (!raceStarted)
		return;
	//UKismetSystemLibrary::PrintString(this, "Update");
	for (FKartRaceInfo& _kartInfo : kartRaceInfos)
	{
		if (!_kartInfo.kart)
			continue;

		ACheckPoint* _nextCheckpoint = GetNextCheckpoint(_kartInfo.currentCheckpoint);
		if (!_nextCheckpoint)
			continue;

		float _distance = FVector::Dist(_kartInfo.kart->GetActorLocation(), _nextCheckpoint->GetActorLocation());
		_kartInfo.distanceToNextCheckpoint = _distance;

		// if near checkpoint
		if (_distance < 200.0f)
		{
			_kartInfo.currentCheckpoint++;
			UKismetSystemLibrary::PrintString(this, "Current CheckPoint : " + FString::FromInt(_kartInfo.currentCheckpoint));

			// if check all the checkpoints
			if (_kartInfo.currentCheckpoint >= checkpoints.Num() - 1)
			{
				_kartInfo.currentCheckpoint = 0;
				_kartInfo.currentLap++;
				UKismetSystemLibrary::PrintString(this, "Current Lap : " + FString::FromInt(_kartInfo.currentLap), true, true, FLinearColor::Yellow, 10.0f);
				onKartLapCompleted.Broadcast(_kartInfo.kart, _kartInfo.currentLap);

				// if finished laps
				if (_kartInfo.currentLap >=  2/*maxLaps*/)
				{
					onRaceFinish.Broadcast(_kartInfo.kart);
					//raceStarted = false;
					UKismetSystemLibrary::PrintString(this, _kartInfo.kart->GetName() + " WON the race !", true, true, FLinearColor::Red, 10.0f);
					break;
				}
				else
				{
					UKismetSystemLibrary::PrintString(this, _kartInfo.kart->GetName() + " completed a lap !", true, true, FLinearColor::Red, 10.0f);
				}
			}
		}
	}

}

ACheckPoint* URaceSubSystem::GetNextCheckpoint(int _currentCheckpointIndex) const
{
	if (checkpoints.Num() == 0)
		return nullptr;

	//return checkpoints[(_currentCheckpointIndex) % checkpoints.Num()];

	int _nextIndex = (_currentCheckpointIndex + 1) % checkpoints.Num();
	return checkpoints[_nextIndex];
}

AKart* URaceSubSystem::GetLeader() const
{
	if (kartRaceInfos.Num() == 0) return nullptr;

    FKartRaceInfo _leader = kartRaceInfos[0];

	for (const FKartRaceInfo& _kartInfo : kartRaceInfos)
	{
		if (_kartInfo.currentLap > _leader.currentLap ||
			(_kartInfo.currentLap == _leader.currentLap && _kartInfo.currentCheckpoint > _leader.currentCheckpoint))
		{
			_leader = _kartInfo;
		}
	}

	return _leader.kart;
}

TArray<AKart*> URaceSubSystem::GetRaceRanking() const
{
	/*for (FKartRaceInfo& _kartInfo : const_cast<TArray<FKartRaceInfo>&>(kartRaceInfos))
	{
		if (_kartInfo.kart)
		{
			ACheckPoint* _nextCheckpoint = GetNextCheckpoint(_kartInfo.currentCheckpoint);
			if (_nextCheckpoint)
			{
				_kartInfo.distanceToNextCheckpoint = FVector::Dist(_kartInfo.kart->GetActorLocation(), _nextCheckpoint->GetActorLocation());
			}
		}
	}*/


	TArray<FKartRaceInfo> _sortedKartInfos = kartRaceInfos;

	_sortedKartInfos.Sort([](const FKartRaceInfo& A, const FKartRaceInfo& B)
		{
			if (A.currentLap != B.currentLap)
			{
				return A.currentLap > B.currentLap; //more lap
			}

			if (A.currentCheckpoint != B.currentCheckpoint)
			{
				return A.currentCheckpoint > B.currentCheckpoint; // more advanced on the race
			}

			return A.distanceToNextCheckpoint < B.distanceToNextCheckpoint; // near of next checkpoint
		});

	TArray<AKart*> _ranking;
	for (const FKartRaceInfo& _kartInfo : _sortedKartInfos)
	{
		_ranking.Add(_kartInfo.kart);
	}

	return _ranking;
}

int URaceSubSystem::GetKartPlacement(AKart* _kart) const
{
	if(!_kart)
		return -1;

	TArray<FKartRaceInfo> _sortedKartInfos = kartRaceInfos;

	_sortedKartInfos.Sort([](const FKartRaceInfo& A, const FKartRaceInfo& B)
		{
			if (A.currentLap != B.currentLap)
			{
				return A.currentLap > B.currentLap; // More laps
			}

			if (A.currentCheckpoint != B.currentCheckpoint)
			{
				return A.currentCheckpoint > B.currentCheckpoint; // far in checkpoints
			}

			return A.distanceToNextCheckpoint < B.distanceToNextCheckpoint; // near next checkpoints
		});

	for (int i = 0; i < _sortedKartInfos.Num(); ++i)
	{
		if (_sortedKartInfos[i].kart == _kart)
		{
			return i + 1; //1st, 2nd , ...
		}
	}

	return -1; // not found
}
