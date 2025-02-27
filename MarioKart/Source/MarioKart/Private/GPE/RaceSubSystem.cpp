#include "GPE/RaceSubSystem.h"
#include "GPE/CheckPoint.h"
#include "3C/Kart.h"
#include <Kismet/KismetSystemLibrary.h>

void URaceSubSystem::RegisterCheckpoint(ACheckPoint* _newCheckpoint)
{
	if (_newCheckpoint)
	{
		checkpoints.Add(_newCheckpoint);
	}
}

ACheckPoint* URaceSubSystem::GetNextCheckpoint(AActor* _player, int _currentCheckpointIndex) const
{
	if (checkpoints.Num() == 0 || _currentCheckpointIndex < 0 || _currentCheckpointIndex >= checkpoints.Num())
	{
		return nullptr;
	}
	// return next checkpoint
	return checkpoints[(_currentCheckpointIndex + 1) % checkpoints.Num()];
}

bool URaceSubSystem::IsGoingWrongWay(AActor* _player, int _currentCheckpointIndex) const
{
	if (!_player || checkpoints.Num() == 0)
	{
		return false;
	}

	ACheckPoint* _nextCheckpoint = GetNextCheckpoint(_player, _currentCheckpointIndex);
	if (!_nextCheckpoint)
	{
		return false;
	}

	FVector _playerDirection = _player->GetVelocity().GetSafeNormal();
	FVector _toCheckpoint = (_nextCheckpoint->GetActorLocation() - _player->GetActorLocation()).GetSafeNormal();

	// if angle between player directin and checkpoint is too hight , wrong way
	float _dotProduct = FVector::DotProduct(_playerDirection, _toCheckpoint);
	return _dotProduct < 0; // < 0 => Wrong way
}

void URaceSubSystem::RegisterKart(AKart* _newKart)
{
	if (!_newKart) return;

	FKartRaceInfo _kartInfo;
	_kartInfo.kart = _newKart;
	kartRaceInfos.Add(_kartInfo);
}

void URaceSubSystem::UpdateRaceProgress()
{
	for (FKartRaceInfo& _kartInfo : kartRaceInfos)
	{
		if (!_kartInfo.kart) continue;

		// check if he is at the next checkpoint
		ACheckPoint* _nextCheckpoint = GetNextCheckpoint(_kartInfo.kart, _kartInfo.currentCheckpoint);
		if (!_nextCheckpoint) continue;

		float _distance = FVector::Dist(_kartInfo.kart->GetActorLocation(), _nextCheckpoint->GetActorLocation());
		_kartInfo.distanceToNextCheckpoint = _distance;

		if (_distance < 200.0f) // if near of checkpoint
		{
			_kartInfo.currentCheckpoint++;

			// if a lap is made
			if (_kartInfo.currentCheckpoint >= checkpoints.Num())
			{
				_kartInfo.currentCheckpoint = 0;
				_kartInfo.currentLap++;

				if (_kartInfo.currentLap >= maxLaps)
				{
					UKismetSystemLibrary::PrintString(this, _kartInfo.kart->GetName() + " won !");
					return; // end race
				}
			}
		}
	}
}

AKart* URaceSubSystem::GetLeader() const
{
	if (kartRaceInfos.Num() == 0) return nullptr;

	FKartRaceInfo _leader = kartRaceInfos[0];

	for (const FKartRaceInfo& KartInfo : kartRaceInfos)
	{
		if (KartInfo.currentLap > _leader.currentLap ||
			(KartInfo.currentLap == _leader.currentLap && KartInfo.currentCheckpoint > _leader.currentCheckpoint))
		{
			_leader = KartInfo;
		}
	}

	return _leader.kart;
}
