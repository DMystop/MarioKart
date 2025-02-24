#include "GPE/RaceSubSystem.h"
#include "GPE/CheckPoint.h"

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
