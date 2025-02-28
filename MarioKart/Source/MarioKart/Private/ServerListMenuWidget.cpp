// Fill out your copyright notice in the Description page of Project Settings.
#include "ServerListMenuWidget.h"
#include <Kismet\KismetSystemLibrary.h>
#include "MainMenuWidget.h"
#include "GIS_Online.h"


void UServerListMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Bind();
	FindSessions();
}

void UServerListMenuWidget::Bind()
{
	backButton->OnClicked.AddDynamic(this, &UServerListMenuWidget::OnBack);
	refreshButton->OnClicked.AddDynamic(this, &UServerListMenuWidget::OnRefresh);
	joinServerButton->OnClicked.AddDynamic(this, &UServerListMenuWidget::OnJoinSession);
}

void UServerListMenuWidget::OnBack()
{
	TObjectPtr<UMainMenuWidget> _mainMenu = CreateWidget<UMainMenuWidget>(GetWorld(), mainMenuRef);
	_mainMenu->AddToViewport();
	RemoveFromParent();
}

void UServerListMenuWidget::OnRefresh()
{
	ClearSessions();
	subsystem->FindSessions();
}

void UServerListMenuWidget::ClearSessions()
{
	for (TObjectPtr<UWidget> _widget : serverList->GetAllChildren())
		_widget->RemoveFromParent();
	allSessions.Empty();
}

TObjectPtr<USessionSlotWidget> UServerListMenuWidget::CreateSessionSlot(const FSessionData& _data, const int& _index)
{
	TObjectPtr<USessionSlotWidget> _sessionSlot = CreateWidget<USessionSlotWidget>(GetWorld(), slotMenuRef);
	_sessionSlot->InitData(_data, _index);
	allSessions.Add(_sessionSlot);
	return _sessionSlot;
}

void UServerListMenuWidget::RemoveSessionSlot(TObjectPtr<USessionSlotWidget> _slot)
{
}

void UServerListMenuWidget::OnSessionsFound(const TArray<FSessionData>& _datas)
{
	const int32& _dataAmount = _datas.Num();
	for (size_t _index = 0; _index < _dataAmount; _index++)
	{
		TObjectPtr<USessionSlotWidget> _session = CreateSessionSlot(_datas[_index], _index);
		_session->OnSelected().AddDynamic(this, &UServerListMenuWidget::OnSessionSelected);
		serverList->AddChild(_session);
	}
}

void UServerListMenuWidget::OnSessionSelected(const FName& _sessionName, const FString& _levelName, const int& _index)
{
	joinServerButton->SetIsEnabled(true);
	sessionName = _sessionName;
	levelName = _levelName;
	sessionIndex = _index;
}

void UServerListMenuWidget::OnJoinSession()
{
	GetSubsystem()->JoinSession(sessionName, levelName, sessionIndex);
}

void UServerListMenuWidget::FindSessions()
{
	if (subsystem = GetSubsystem())
	{
		subsystem->OnSessionsFound().AddDynamic(this, &UServerListMenuWidget::OnSessionsFound);
		subsystem->FindSessions();
	}
}