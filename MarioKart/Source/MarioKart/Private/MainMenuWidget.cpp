// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "ServerListMenuWidget.h"
#include <ServerListMenuWidget.h>


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitBinding();
}

void UMainMenuWidget::InitBinding()
{
	playButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayButton);
	quitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitButton);
	searchButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSearchButton);
}


void UMainMenuWidget::OnPlayButton()
{
	UE_LOG(LogTemp, Warning, TEXT("Play"));
	GetWorld()->ServerTravel("/Game/Levels/LVL_Lobby?listen");
	
}

void UMainMenuWidget::OnQuitButton()
{
	UE_LOG(LogTemp, Warning, TEXT("Quit"));
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnSearchButton()
{
	UE_LOG(LogTemp, Warning, TEXT("Search"));
	TObjectPtr<UServerListMenuWidget> _serverListMenu = CreateWidget<UServerListMenuWidget>(GetWorld(), serverListMenuRef);
	_serverListMenu->AddToViewport();
	RemoveFromParent();
}

