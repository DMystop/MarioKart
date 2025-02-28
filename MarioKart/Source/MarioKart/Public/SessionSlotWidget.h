// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GIS_Online.h"

#include "SessionSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class MARIOKART_API USessionSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSelected, const FName&, _sessionName, const FString&, _level, const int&, _index);
	UPROPERTY() FOnSelected onSelected;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> joinButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UTextBlock> serverName;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UTextBlock> levelName;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UTextBlock> currentPlayers;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UTextBlock> maxPlayers;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UTextBlock> ping;
	UPROPERTY() int index;

public:
	FORCEINLINE FOnSelected& OnSelected() { return onSelected; }

private:
	virtual void NativeConstruct() override;
	void Bind();
	UFUNCTION() void OnJoin();

public:
	void InitData(const FSessionData& _data, const int& _index);
};
