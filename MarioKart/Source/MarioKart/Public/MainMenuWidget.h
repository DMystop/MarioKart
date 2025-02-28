// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
// #include "ServerListMenuWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
class UServerListMenuWidget;
UCLASS()
class MARIOKART_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Buttons") TSubclassOf<UServerListMenuWidget> serverListMenuRef;

	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidget)) TObjectPtr<UButton> playButton = nullptr;
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidget)) TObjectPtr<UTextBlock> playTextButton = nullptr;	
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidget)) TObjectPtr<UButton> quitButton = nullptr;
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidget)) TObjectPtr<UTextBlock> quitTextButton = nullptr;	
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidget)) TObjectPtr<UButton> searchButton = nullptr;
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidget)) TObjectPtr<UTextBlock> searchTextButton = nullptr;
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidget)) TObjectPtr<UImage> mainMenuImage = nullptr;

	virtual void NativeConstruct() override;
	void InitBinding();
	UFUNCTION() void OnPlayButton();
	UFUNCTION() void OnQuitButton();
	UFUNCTION() void OnSearchButton();

	void LoadLevel();
	
};
