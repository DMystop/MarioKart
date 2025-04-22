#include "GPE/CheckPoint.h"
#include "GPE/RaceSubSystem.h"
#include "3C/Kart.h"
#include <Kismet/KismetSystemLibrary.h>

ACheckPoint::ACheckPoint()
{
	PrimaryActorTick.bCanEverTick = false;
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
	/*AKart* _playerKart = Cast<AKart>(_otherActor);
	if (_playerKart)
	{
		if (_playerKart->HasAuthority())
		{
			_playerKart->ValidateCheckpoint(this);

			onCheckpointValidated.Broadcast(_playerKart, this);
		}
		else
		{
			UKismetSystemLibrary::PrintString(this, "Client");
			_playerKart->Server_ValidateCheckpoint(this);
		}
	}*/

	AKart* _playerKart = Cast<AKart>(_otherActor);
	if (!_playerKart) return;

	// SERVER
	if (_playerKart->HasAuthority())
	{
		UKismetSystemLibrary::PrintString(this, "Server: Validate Checkpoint for " + _playerKart->GetName());
		_playerKart->ValidateCheckpoint(this);
		onCheckpointValidated.Broadcast(_playerKart, this);
	}
	// CLIENT
	/*else if (_playerKart->IsLocallyControlled())
	{
		UKismetSystemLibrary::PrintString(this, "Client: Ask Server to Validate Checkpoint");
		_playerKart->Server_ValidateCheckpoint(this);
	}*/

}


