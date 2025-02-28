// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby_HUD.h"

void ALobby_HUD::BeginPlay()
{
	Super::BeginPlay();
	InitUI();
}


void ALobby_HUD::InitUI()
{
	currentLobby = CreateWidget<ULobbyWidget>(GetWorld(), lobbyWidget);
	if (currentLobby)
		currentLobby->AddToViewport();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

}
