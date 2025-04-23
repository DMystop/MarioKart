// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "DashboardWidget.generated.h"

/**
 * 
 */
class AItem;
UCLASS()
class MARIOKART_API UDashboardWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UTextBlock> coinCount = nullptr;

	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UTextBlock> playerRank = nullptr;

	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UTextBlock> currentLap = nullptr;
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UTextBlock> totalLaps = nullptr;

	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UImage> firstItemSlot = nullptr;
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UImage> secondItemSlot = nullptr;

public:
    void SetItemImage(TObjectPtr<UImage> _image, UTexture2D* _newImage);
    void UpdateItemsDashboard(const TArray<TSubclassOf<AItem>>& Items);
	void SetTextValue(UTextBlock* textBlock, int32 value);
    void UpdateCoinDashboard(const int _coinCount);
    void UpdateCurrentLapsDashboard(const int _currentLap);
    void UpdateTotalLapsDashboard(const int _totalLaps);
	void UpdatePlayerRankDashboard(const int _playerRank);


private:
	virtual void NativeConstruct() override;
};
