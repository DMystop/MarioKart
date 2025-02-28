// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuWidget.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class MARIOKART_API AMenuHUD : public AHUD
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "MainMenu") TSubclassOf<UMainMenuWidget> mainMenuWidget = nullptr;
	UPROPERTY() TObjectPtr<UMainMenuWidget> currentMainMenu = nullptr;
public:
	FORCEINLINE TObjectPtr<UMainMenuWidget> GetCurrentMainMenu() { return currentMainMenu; }
	virtual void BeginPlay() override;
	void InitUI();
};
