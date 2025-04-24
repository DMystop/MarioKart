// Fill out your copyright notice in the Description page of Project Settings.


#include "Dashboard_HUD.h"
#include <Kismet/KismetSystemLibrary.h>

void ADashboard_HUD::BeginPlay()
{
	Super::BeginPlay();
	InitUI();

	if (dashboardWidget)
	{
		currentDashboard = CreateWidget<UDashboardWidget>(GetWorld(), dashboardWidget);
		if (currentDashboard)
		{
			currentDashboard->AddToViewport();
			FTimerHandle _timer;
			GetWorldTimerManager().SetTimer(_timer, [&]() { onWidgetLoaded.Broadcast(); }, 1.0f, false);
			UKismetSystemLibrary::PrintString(this, "Hallo", true, true, FLinearColor::Red, 10.0f);
		}
	}
}

void ADashboard_HUD::InitUI()
{
	currentDashboard = CreateWidget<UDashboardWidget>(GetWorld(), dashboardWidget);
	if (currentDashboard)
		currentDashboard->AddToViewport();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}
