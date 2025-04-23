#include "GPE/RaceGameMode.h"
#include "GPE/RaceSubSystem.h"
#include <Kismet/KismetSystemLibrary.h>
#include "3C/Kart.h"


ARaceGameMode::ARaceGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	//bStartPlayersAsSpectators = true; // Start wait mode
}

void ARaceGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		StartRaceCountdown();
	}
}

void ARaceGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	URaceSubSystem* _raceSubSystem = GetGameInstance()->GetSubsystem<URaceSubSystem>();
	if (raceState == ERaceState::PROGRESS)
	{
		if (_raceSubSystem)
		{
			AKart* _leader = _raceSubSystem->GetLeader();
			if (_leader && _leader->GetLapCompleted() >= _raceSubSystem->GetMaxLaps())
			{
				FinishRace(_leader);
			}

			if(HasAuthority())
				_raceSubSystem->UpdateRaceProgress();

			TArray<AKart*> _ranking = _raceSubSystem->GetRaceRanking();

			FString _rankingString = "Leaderboard :\n";

			for (int i = 0; i < _ranking.Num(); ++i)
			{
				if (_ranking[i])
				{
					_rankingString += FString::Printf(TEXT("%d. %s\n"), i + 1, *_ranking[i]->GetName());
				}
			}

			UKismetSystemLibrary::PrintString(this, _rankingString, true, true, FLinearColor::Yellow, 0.0f);
		}
	}

}

void ARaceGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARaceGameMode, raceState);
}

void ARaceGameMode::StartRaceCountdown()
{
	if (!HasAuthority()) return;

	countdownRemainingTime = countdownTime;

	GetWorldTimerManager().SetTimer(countdownTimerHandle, this, &ARaceGameMode::CountdownTick, 1.0f, true);
}

void ARaceGameMode::CountdownTick()
{
	countdownRemainingTime--;


	if (countdownRemainingTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(countdownTimerHandle);
		StartRace();
	}
}

void ARaceGameMode::StartRace()
{
	raceState = ERaceState::PROGRESS;
	URaceSubSystem* _raceSubSystem = GetGameInstance()->GetSubsystem<URaceSubSystem>();
	_raceSubSystem->StartRace();
	//Enable movements
}

void ARaceGameMode::FinishRace(AKart* _winningKart)
{
	raceState = ERaceState::FINISH;
}
