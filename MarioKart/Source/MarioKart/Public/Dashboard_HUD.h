// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <DashboardWidget.h>
#include "Dashboard_HUD.generated.h"

/**
 * 
 */
UCLASS()
class MARIOKART_API ADashboard_HUD : public AHUD
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "Dashboard") TSubclassOf<UDashboardWidget> dashboardWidget = nullptr;
	UPROPERTY() TObjectPtr<UDashboardWidget> currentDashboard = nullptr;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetLoaded);
	FOnWidgetLoaded onWidgetLoaded;

public:
	FORCEINLINE FOnWidgetLoaded& OnWidgetLoaded() { return onWidgetLoaded; }
	FORCEINLINE TObjectPtr<UDashboardWidget> GetCurrentDashboard() { return currentDashboard; }
	virtual void BeginPlay() override;
	void InitUI();
};