#include "GPE/RaceGameMode.h"
#include "GPE/RaceSubSystem.h"
#include <Kismet/KismetSystemLibrary.h>
#include "3C/Kart.h"

void ARaceGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UGameInstance* _gameInstance = GetWorld()->GetGameInstance())
	{
		raceSubSystem = _gameInstance->GetSubsystem<URaceSubSystem>();
	}

	if (raceSubSystem)
	{
		GetWorldTimerManager().SetTimer(rankingTimerHandle, this, &ARaceGameMode::ShowRaceRanking, 3.0f, true);
	}
}

void ARaceGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	raceSubSystem->UpdateRaceProgress();
}

void ARaceGameMode::ShowRaceRanking()
{
	if (!raceSubSystem) return;

	TArray<AKart*> _raceRanking = raceSubSystem->GetRaceRanking();

	for (int i = 0; i < _raceRanking.Num(); i++)
	{
		UKismetSystemLibrary::PrintString(this, FString::FromInt((i + 1)) + _raceRanking[i]->GetName());
	}

	CheckRaceEnd();
}

void ARaceGameMode::CheckRaceEnd()
{
	if (!raceSubSystem) return;

	for (const FKartRaceInfo& _kartInfo : raceSubSystem->GetKartInfosRaces())
	{
		if (_kartInfo.currentLap >= raceSubSystem->MaxLaps())
		{
			GetWorldTimerManager().ClearTimer(rankingTimerHandle);
			UKismetSystemLibrary::PrintString(this," Course terminée !" );

			return;
		}
	}
}
