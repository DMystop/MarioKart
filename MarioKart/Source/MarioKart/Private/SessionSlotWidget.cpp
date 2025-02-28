// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionSlotWidget.h"

void USessionSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Bind();
}

void USessionSlotWidget::Bind()
{
	if (joinButton == nullptr)
	{
		LOG("UUW_SessionSlot => joinButton null", Yellow);
		return;
	}
	joinButton->OnClicked.AddDynamic(this, &USessionSlotWidget::OnJoin);
}

void USessionSlotWidget::OnJoin()
{
	//onSelected.Broadcast(FName(serverName->Text.ToString()), levelName.GetName(), index);
	onSelected.Broadcast(FName(serverName->Text.ToString()), levelName->Text.ToString(), index);
	LOG("ON Join" + levelName->Text.ToString(), Yellow);

}

void USessionSlotWidget::InitData(const FSessionData& _data, const int& _index)
{
	serverName->SetText(FText::FromString(_data.serverName));
	levelName->SetText(FText::FromString(_data.levelName));
	currentPlayers->SetText(FText::FromString(FString::FromInt(_data.playersCount)));
	maxPlayers->SetText(FText::FromString((FString::FromInt(_data.maxPlayersCount))));
	ping->SetText(FText::FromString((FString::FromInt(_data.ping)) + "ms"));
	index = _index;
}
