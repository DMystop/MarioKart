#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RaceGameMode.generated.h"

class URaceSubSystem;
class AKart;

UCLASS()
class MARIOKART_API ARaceGameMode : public AGameModeBase
{
	GENERATED_BODY()
	UPROPERTY()TObjectPtr<URaceSubSystem> raceSubSystem;
	FTimerHandle rankingTimerHandle;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void ShowRaceRanking();
	void CheckRaceEnd();
	
};
