// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_Lobby.h"
#include <GIS_Online.h>

void APC_Lobby::BeginPlay()
{
	Super::BeginPlay();
	// LOG("APCLOBBY 1", Magenta);
	if (this != GetWorld()->GetFirstPlayerController())
		return;
	// LOG("APCLOBBY 2", Magenta);
	FTimerHandle _timer;
	FTimerDelegate _delegate = FTimerDelegate();
	_delegate.BindLambda([&]()
		{
			if (UGIS_Online* _online = GetWorld()->GetGameInstance()->GetSubsystem<UGIS_Online>())
			{
				if (HasAuthority())
				{
					LOG("APC_Lobby => Create session with authority!", Magenta);
					_online->CreateSession();
					_online->StartSession();
				}
			}
		});
	GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, 0.1f, false);
}
