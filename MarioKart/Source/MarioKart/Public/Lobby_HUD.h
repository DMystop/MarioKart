// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <LobbyWidget.h>
#include "Lobby_HUD.generated.h"

/**
 * 
 */
UCLASS()
class MARIOKART_API ALobby_HUD : public AHUD
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "lobby") TSubclassOf<ULobbyWidget> lobbyWidget = nullptr;
	UPROPERTY() TObjectPtr<ULobbyWidget> currentLobby = nullptr;
public:
	FORCEINLINE TObjectPtr<ULobbyWidget> GetCurrentLobby() { return currentLobby; }
	virtual void BeginPlay() override;
	void InitUI();
};
