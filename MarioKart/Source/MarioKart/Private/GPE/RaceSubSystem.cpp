#include "GPE/RaceSubSystem.h"
#include "GPE/CheckPoint.h"
#include "3C/Kart.h"
#include <Kismet/KismetSystemLibrary.h>

//void URaceSubSystem::RegisterCheckpoint(ACheckPoint* _newCheckpoint)
//{
//	if (_newCheckpoint)
//	{
//		UKismetSystemLibrary::PrintString(this, "Register CheckPoint");
//		checkpoints.Add(_newCheckpoint);
//	}
//}

//ACheckPoint* URaceSubSystem::GetNextCheckpoint(AActor* _player, int _currentCheckpointIndex) const
//{
//	if (checkpoints.Num() == 0 || _currentCheckpointIndex < 0 || _currentCheckpointIndex >= checkpoints.Num())
//	{
//		return nullptr;
//	}
//	// return next checkpoint
//	return checkpoints[(_currentCheckpointIndex + 1) % checkpoints.Num()];
//}
//
//bool URaceSubSystem::IsGoingWrongWay(AActor* _player, int _currentCheckpointIndex) const
//{
//	if (!_player || checkpoints.Num() == 0)
//	{
//		return false;
//	}
//
//	ACheckPoint* _nextCheckpoint = GetNextCheckpoint(_player, _currentCheckpointIndex);
//	if (!_nextCheckpoint)
//	{
//		return false;
//	}
//
//	FVector _playerDirection = _player->GetVelocity().GetSafeNormal();
//	FVector _toCheckpoint = (_nextCheckpoint->GetActorLocation() - _player->GetActorLocation()).GetSafeNormal();
//
//	// if angle between player directin and checkpoint is too hight , wrong way
//	float _dotProduct = FVector::DotProduct(_playerDirection, _toCheckpoint);
//	return _dotProduct < 0; // < 0 => Wrong way
//}
//
//void URaceSubSystem::RegisterKart(AKart* _newKart)
//{
//	if (!_newKart) return;
//
//	FKartRaceInfo _kartInfo;
//	_kartInfo.kart = _newKart;
//	kartRaceInfos.Add(_kartInfo);
//}
//
//void URaceSubSystem::UpdateRaceProgress()
//{
//	for (FKartRaceInfo& _kartInfo : kartRaceInfos)
//	{
//		UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(2.0f));
//
//		if (!_kartInfo.kart) continue;
//
//		// check if he is at the next checkpoint
//		ACheckPoint* _nextCheckpoint = GetNextCheckpoint(_kartInfo.kart, _kartInfo.currentCheckpoint);
//		if (!_nextCheckpoint) continue;
//
//		float _distance = FVector::Dist(_kartInfo.kart->GetActorLocation(), _nextCheckpoint->GetActorLocation());
//		_kartInfo.distanceToNextCheckpoint = _distance;
//		UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(_distance));
//
//		if (_distance < 200.0f) // if near of checkpoint
//		{
//			_kartInfo.currentCheckpoint++;
//
//			// if a lap is made
//			if (_kartInfo.currentCheckpoint >= checkpoints.Num())
//			{
//				_kartInfo.currentCheckpoint = 0;
//				_kartInfo.currentLap++;
//				UKismetSystemLibrary::PrintString(this, " Next laps !");
//
//				if (_kartInfo.currentLap >= maxLaps)
//				{
//					UKismetSystemLibrary::PrintString(this, _kartInfo.kart->GetName() + " won !");
//					return; // end race
//				}
//			}
//		}
//	}
//}
//
//AKart* URaceSubSystem::GetLeader() const
//{
//	if (kartRaceInfos.Num() == 0) return nullptr;
//
//	FKartRaceInfo _leader = kartRaceInfos[0];
//
//	for (const FKartRaceInfo& KartInfo : kartRaceInfos)
//	{
//		if (KartInfo.currentLap > _leader.currentLap ||
//			(KartInfo.currentLap == _leader.currentLap && KartInfo.currentCheckpoint > _leader.currentCheckpoint))
//		{
//			_leader = KartInfo;
//		}
//	}
//
//	return _leader.kart;
//}
//
//TArray<AKart*> URaceSubSystem::GetRaceRanking() const
//{
//	TArray<FKartRaceInfo> _sortedKartInfos = kartRaceInfos;
//
//	_sortedKartInfos.Sort([](const FKartRaceInfo& A, const FKartRaceInfo& B)
//		{
//			if (A.currentLap != B.currentLap)
//			{
//				return A.currentLap > B.currentLap; 
//			}
//
//			if (A.currentCheckpoint != B.currentCheckpoint)
//			{
//				return A.currentCheckpoint > B.currentCheckpoint; 
//			}
//
//			return A.distanceToNextCheckpoint < B.distanceToNextCheckpoint; 
//		});
//
//	TArray<AKart*> _ranking;
//	for (const FKartRaceInfo& _kartInfo : _sortedKartInfos)
//	{
//		_ranking.Add(_kartInfo.kart);
//	}
//
//	return _ranking;
//}





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

	UKismetSystemLibrary::PrintString(this, "Race Started !");
}

void URaceSubSystem::UpdateRaceProgress()
{
	if (!raceStarted)
		return;

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

			// if check all the checkpoints
			if (_kartInfo.currentCheckpoint >= checkpoints.Num())
			{
				_kartInfo.currentCheckpoint = 0;
				_kartInfo.currentLap++;

				onKartLapCompleted.Broadcast(_kartInfo.kart, _kartInfo.currentLap);

				// if finished laps
				if (_kartInfo.currentLap >= maxLaps)
				{
					onRaceFinish.Broadcast(_kartInfo.kart);
					raceStarted = false;
					UKismetSystemLibrary::PrintString(this, _kartInfo.kart->GetName() + " WON the race !");
					break;
				}
				else
				{
					UKismetSystemLibrary::PrintString(this, _kartInfo.kart->GetName() + " completed a lap !");
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
