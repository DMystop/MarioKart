#include "GPE/CheckPoint.h"
#include "GPE/RaceSubSystem.h"
#include "3C/Kart.h"
#include <Kismet/KismetSystemLibrary.h>

ACheckPoint::ACheckPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(true);
	OnActorBeginOverlap.AddDynamic(this, &ACheckPoint::OnCheckPointOverlap);
}

void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

void ACheckPoint::Init()
{
	if (UGameInstance* _gameInstance = GetGameInstance())
	{
		if (URaceSubSystem* _raceSubsystem = _gameInstance->GetSubsystem<URaceSubSystem>())
		{
			_raceSubsystem->RegisterCheckpoint(this);
		}
	}
}

void ACheckPoint::OnCheckPointOverlap(AActor* _overlappedActor, AActor* _otherActor)
{
	AKart* _playerKart = Cast<AKart>(_otherActor);
	if (_playerKart)
	{
		if (UGameInstance* _gameInstance = GetGameInstance())
		{
			if (URaceSubSystem* _raceSubsystem = _gameInstance->GetSubsystem<URaceSubSystem>())
			{
				int _checkpointIndex = _raceSubsystem->GetCheckpoints().Find(this);
				if (_checkpointIndex != INDEX_NONE)
				{
					_playerKart->SetCurrentCheckpoint(_checkpointIndex);
					UKismetSystemLibrary::PrintString(this, "Check");
				}
			}
		}
	}
}


