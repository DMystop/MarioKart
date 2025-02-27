#include "GPE/CheckPoint.h"
#include "GPE/RaceSubSystem.h"

ACheckPoint::ACheckPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	OnActorBeginOverlap.AddDynamic(this, &ACheckPoint::OnCheckPointOverlap);
}

void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

void ACheckPoint::Init()
{
	/*if (UGameInstance* _gameInstance = GetGameInstance())
	{
		if (URaceSubSystem* _raceSubsystem = _gameInstance->GetSubsystem<URaceSubSystem>())
		{
			_raceSubsystem->RegisterCheckpoint(this);
		}
	}*/
}

void ACheckPoint::OnCheckPointOverlap(AActor* _overlappedActor, AActor* _otherActor)
{
	/*AKartPawn* _playerKart = Cast<AKartPawn>(OtherActor);
	if (_playerKart)
	{
		_playerKart->SetCurrentCheckpoint(this);
	}*/
}


