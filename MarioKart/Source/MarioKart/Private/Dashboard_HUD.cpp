// Fill out your copyright notice in the Description page of Project Settings.


#include "Dashboard_HUD.h"

void ADashboard_HUD::BeginPlay()
{
	Super::BeginPlay();
	InitUI();
}

void ADashboard_HUD::InitUI()
{
	currentDashboard = CreateWidget<UDashboardWidget>(GetWorld(), dashboardWidget);
	if (currentDashboard)
		currentDashboard->AddToViewport();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}
