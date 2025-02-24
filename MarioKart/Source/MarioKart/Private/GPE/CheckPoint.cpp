#include "GPE/CheckPoint.h"
#include "GPE/RaceSubSystem.h"

ACheckPoint::ACheckPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	collisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	RootComponent = collisionBox;
	collisionBox->SetCollisionProfileName("Trigger");

}

void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

void ACheckPoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
	/*AKartPawn* _playerKart = Cast<AKartPawn>(OtherActor);
	if (_playerKart)
	{
		_playerKart->SetCurrentCheckpoint(this);
	}*/
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


