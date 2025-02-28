// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "GIS_Online.h"
#include "SessionSlotWidget.h"
#include "MainMenuWidget.h"
#include "ServerListMenuWidget.generated.h"

UCLASS()
class MARIOKART_API UServerListMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> mainMenuRef;
	UPROPERTY(EditAnywhere) TSubclassOf<USessionSlotWidget> slotMenuRef;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UScrollBox> serverList;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> backButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> refreshButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UButton> joinServerButton;
	UPROPERTY() TObjectPtr<UGIS_Online> subsystem;
	UPROPERTY() TArray<TObjectPtr<USessionSlotWidget>> allSessions;
	UPROPERTY() FName sessionName;
	UPROPERTY() FString levelName;
	UPROPERTY() int sessionIndex;

private:
	FORCEINLINE TObjectPtr<UGIS_Online> GetSubsystem() const { return subsystem ? subsystem.Get() : GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>(); }

private:
	virtual void NativeConstruct() override;

private:
	void Bind();
	void FindSessions();
	UFUNCTION() void OnRefresh();
	void ClearSessions();
	TObjectPtr<USessionSlotWidget> CreateSessionSlot(const FSessionData& _data, const int& _index);
	void RemoveSessionSlot(TObjectPtr<USessionSlotWidget> _slot);
	UFUNCTION() void OnBack();
	UFUNCTION() void OnSessionsFound(const TArray<FSessionData>& _datas);
	UFUNCTION() void OnSessionSelected(const FName& _sessionName, const FString& _levelName, const int& _index);
	UFUNCTION() void OnJoinSession();
};
