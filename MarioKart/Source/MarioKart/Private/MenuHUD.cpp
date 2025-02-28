// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	InitUI();
}


void AMenuHUD::InitUI()
{
	currentMainMenu = CreateWidget<UMainMenuWidget>(GetWorld(), mainMenuWidget);
	if (currentMainMenu)
		currentMainMenu->AddToViewport();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

