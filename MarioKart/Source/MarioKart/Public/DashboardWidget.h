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
UCLASS()
class MARIOKART_API UDashboardWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UTextBlock> coinCount = nullptr;

	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UTextBlock> playerRank = nullptr;

	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UTextBlock> currentLap = nullptr;
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UTextBlock> totalLaps = nullptr;

	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UImage> firstItemImage = nullptr;
	UPROPERTY(EditAnywhere, Category = "Buttons", meta = (BindWidgetOptional)) TObjectPtr<UImage> secondItemImage = nullptr;

public:
    FORCEINLINE TObjectPtr<UTextBlock> GetCoinCount() const { return coinCount; }
    FORCEINLINE void SetCoinCount(TObjectPtr<UTextBlock> InCoinCount) { coinCount = InCoinCount; }

    FORCEINLINE TObjectPtr<UTextBlock> GetPlayerRank() const { return playerRank; }
    FORCEINLINE void SetPlayerRank(TObjectPtr<UTextBlock> InPlayerRank) { playerRank = InPlayerRank; }

    FORCEINLINE TObjectPtr<UTextBlock> GetCurrentLap() const { return currentLap; }
    FORCEINLINE void SetCurrentLap(TObjectPtr<UTextBlock> InCurrentLap) { currentLap = InCurrentLap; }

    FORCEINLINE TObjectPtr<UTextBlock> GetTotalLaps() const { return totalLaps; }
    FORCEINLINE void SetTotalLaps(TObjectPtr<UTextBlock> InTotalLaps) { totalLaps = InTotalLaps; }

    FORCEINLINE TObjectPtr<UImage> GetFirstItemImage() const { return firstItemImage; }
    FORCEINLINE void SetFirstItemImage(TObjectPtr<UImage> InFirstItemImage) { firstItemImage = InFirstItemImage; }

    FORCEINLINE TObjectPtr<UImage> GetSecondItemImage() const { return secondItemImage; }
    FORCEINLINE void SetSecondItemImage(TObjectPtr<UImage> InSecondItemImage) { secondItemImage = InSecondItemImage; }
private:
	virtual void NativeConstruct() override;
	void InitBinding();

};
