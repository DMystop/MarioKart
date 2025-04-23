#include "DashboardWidget.h"
#include "GPE/Item.h"
#include <Kismet/KismetSystemLibrary.h>

void UDashboardWidget::SetItemImage(TObjectPtr<UImage> _image, UTexture2D* _newItemTexture)
{
	if (_image) _image->SetBrushFromTexture(_newItemTexture, true);
}

void UDashboardWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDashboardWidget::UpdateItemsDashboard(const TArray<TSubclassOf<AItem>>& _items)
{
	firstItemSlot->SetBrushFromTexture(nullptr);
	secondItemSlot->SetBrushFromTexture(nullptr);

	for (int _i = 0; _i < _items.Num(); ++_i)
	{
		AItem* _tempItem = GetWorld()->SpawnActor<AItem>(_items[_i]);
		if (!_tempItem) continue;

		if (_i == 0 && _tempItem->GetItemImage())
		{
			firstItemSlot->SetBrushFromTexture(_tempItem->GetItemImage());
		}
		else if (_i == 1 && _tempItem->GetItemImage())
			secondItemSlot->SetBrushFromTexture(_tempItem->GetItemImage());

		_tempItem->Destroy();
	}
}

void UDashboardWidget::SetTextValue(UTextBlock* textBlock, int32 value)
{
	if (textBlock)
	{
		textBlock->SetText(FText::AsNumber(value));
	}
}

void UDashboardWidget::UpdateCoinDashboard(const int _coinCount)
{
	SetTextValue(coinCount, _coinCount);
}

void UDashboardWidget::UpdateCurrentLapsDashboard(const int _currentLap)
{
	SetTextValue(currentLap, _currentLap);
}

void UDashboardWidget::UpdateTotalLapsDashboard(const int _totalLaps)
{
	SetTextValue(totalLaps, _totalLaps);
}

void UDashboardWidget::UpdatePlayerRankDashboard(const int _playerRank)
{
	
	SetTextValue(playerRank, _playerRank);
}

