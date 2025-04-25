#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "RaceGameMode.generated.h"

class URaceSubSystem;
class AKart;

UENUM(BlueprintType)
enum class ERaceState : uint8
{
	WAIT,
	PROGRESS,
	FINISH,
};

UCLASS()
class MARIOKART_API ARaceGameMode : public AGameModeBase
{
	GENERATED_BODY()
	/*UPROPERTY()TObjectPtr<URaceSubSystem> raceSubSystem;
	FTimerHandle rankingTimerHandle;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void ShowRaceRanking();
	void CheckRaceEnd();*/

protected:
	UPROPERTY(Replicated) ERaceState raceState = ERaceState::WAIT;
	UPROPERTY(EditDefaultsOnly)float countdownTime = 3.0f;
	FTimerHandle countdownTimerHandle;
	float countdownRemainingTime = 0.0f;
	TArray<APlayerStart*> spawnList;

public:
	ARaceGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void SearchSpawn();
	int32 SpawnIndexForController(AController* Player) const;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)void StartRaceCountdown();

protected:
	void CountdownTick();
	void StartRace();
	void FinishRace(AKart* _winningKart);

	
};
