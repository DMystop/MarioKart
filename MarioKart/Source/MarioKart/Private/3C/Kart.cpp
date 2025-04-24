// Fill out your copyright notice in the Description page of Project Settings.


#include "3C/Kart.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include"3C/KartMovementComponent.h"
#include"3C/StunComponentComponent.h"
#include "3C/InventoryComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Dashboard_HUD.h>
#include "GPE/CheckPoint.h"



// Sets default values
AKart::AKart()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	arm = CreateDefaultSubobject<USpringArmComponent>("Spring");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");


	movement = CreateDefaultSubobject<UKartMovementComponent>("Movemnt");
	inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	stunComponent = CreateDefaultSubobject<UStunComponent>("Stun");

	arm->SetupAttachment(RootComponent);
	camera->SetupAttachment(arm);
	mesh->SetupAttachment(RootComponent);

	AddOwnedComponent(movement);
	AddOwnedComponent(inventory);
	AddOwnedComponent(stunComponent);

	bReplicates = true;
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void AKart::BeginPlay()
{
	Super::BeginPlay();

	InitInput();
	Init();
	ENetRole _role = GetLocalRole();
	const UEnum* EnumPtr = StaticEnum<ENetRole>();
	FString _msg = "Local Role =>" + EnumPtr->GetDisplayNameTextByValue(_role).ToString();
	UKismetSystemLibrary::PrintString(this, _msg);
	Bind();
}

void AKart::Bind()
{
	stunComponent->OnStun().AddDynamic(movement.Get(), &UKartMovementComponent::SetMoveStun);
	stunComponent->OnStun().AddDynamic(inventory.Get(), &UInventoryComponent::SetCanUseOnStun);
}

// Called every frame
void AKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	int _placement = raceSubSystem->GetKartPlacement(this);
	FString _string = "Player placement : ";
	_string += FString::Printf(TEXT("%d. %s\n"), _placement);
	//UKismetSystemLibrary::PrintString(this, _string);

}

void AKart::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AKart, currentCheckPointIndex);
	DOREPLIFETIME(AKart, currentLap);
}

// Called to bind functionality to input
void AKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* _input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	_input->BindAction(input.accelerateAction, ETriggerEvent::Triggered, movement.Get(), &UKartMovementComponent::Accelerate);
	_input->BindAction(input.accelerateAction, ETriggerEvent::Completed, movement.Get(), &UKartMovementComponent::SetAddVelocity);
	_input->BindAction(input.brakeAction, ETriggerEvent::Triggered, movement.Get(), &UKartMovementComponent::Brake);
	_input->BindAction(input.brakeAction, ETriggerEvent::Completed, movement.Get(), &UKartMovementComponent::SetAddVelocity);
	_input->BindAction(input.turnAction, ETriggerEvent::Triggered, movement.Get(), &UKartMovementComponent::Rotate);
	_input->BindAction(input.turnAction, ETriggerEvent::Completed, movement.Get(), &UKartMovementComponent::Rotate);
	_input->BindAction(input.boostAction, ETriggerEvent::Started, movement.Get(), &UKartMovementComponent::Boost);
	_input->BindAction(input.useAction, ETriggerEvent::Started, inventory.Get(), &UInventoryComponent::UseItem);
	_input->BindAction(input.shootBehindAction, ETriggerEvent::Started, this, &AKart::ToggleShootDirection);
	_input->BindAction(input.shootBehindAction, ETriggerEvent::Completed, this, &AKart::ToggleShootDirection);
	_input->BindAction(input.stunAction, ETriggerEvent::Started, stunComponent.Get(), &UStunComponent::StunAction);
	_input->BindAction(input.driftAction, ETriggerEvent::Started, movement.Get(), &UKartMovementComponent::DriftEnter);
	_input->BindAction(input.driftAction, ETriggerEvent::Completed, movement.Get(), &UKartMovementComponent::DriftOut);

}

void AKart::InitInput()
{
	ULocalPlayer* _local = GetWorld()->GetFirstLocalPlayerFromController();

	UEnhancedInputLocalPlayerSubsystem* _inputSystem = _local->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	_inputSystem->AddMappingContext(input.mappingContext, 0);
}

void AKart::Init()
{
	UKismetSystemLibrary::PrintString(this, "Hallo222", true, true, FLinearColor::Red, 10.0f);
	ENetMode NetMode = GetWorld()->GetNetMode();
	// on veut binder uniquement sur le client local (ou sur le listen-server local)
	if (NetMode == NM_Client || (NetMode == NM_ListenServer && IsLocallyControlled()))
	{
		TryBindToHUD();
	}

	raceSubSystem = GetWorld()->GetGameInstance()->GetSubsystem<URaceSubSystem>();
	if (raceSubSystem)
	{
		raceSubSystem->RegisterKart(this);
		UKismetSystemLibrary::PrintString(this, "Register Kart");
	}
}

void AKart::TryBindToHUD()
{
	if (isBoundToHUD) return;

	if (ADashboard_HUD* _HUD = GetDashboardHUD())
	{
		_HUD->OnWidgetLoaded().AddDynamic(this, &AKart::ApplyTotalLapsToDashboard);
		isBoundToHUD = true;
		UKismetSystemLibrary::PrintString(this, TEXT("Bind HUD réussi"), true, true, FLinearColor::Green, 5.0f);
	}
	else
	{
		FTimerHandle _retryTimer;
		GetWorldTimerManager().SetTimer(_retryTimer, this, &AKart::TryBindToHUD, 0.2f, false);
	}
}

void AKart::ApplyTotalLapsToDashboard()
{
	UKismetSystemLibrary::PrintString(this, "Coucou" + FString::FromInt(maxLap), true, true, FLinearColor::Red, 10.0f);
	GetDashboardWidget()->UpdateTotalLapsDashboard(maxLap);
}

void AKart::ToggleShootDirection(const FInputActionValue& _value)
{
	bool _shootBehind = _value.Get<bool>();
	UKismetSystemLibrary::PrintString(this, _shootBehind ? "True" : "False");
	shootBehind = _shootBehind;
}

void AKart::SetCurrentCheckpoint(int _checkpoint)
{
	if (!raceSubSystem) return;

	if (_checkpoint == 0 && currentCheckPointIndex == raceSubSystem->GetTotalCheckpoints() - 1)
	{
		lapsCompleted++;
		if (lapsCompleted >= 3) // 3 laps
		{
			UKismetSystemLibrary::PrintString(this, "Finish");
			return;
		}
	}


	currentCheckPointIndex = _checkpoint;
	raceSubSystem->UpdateRaceProgress();
}



void AKart::ValidateCheckpoint(ACheckPoint* _checkpoint)
{
	if (!raceSubSystem || !_checkpoint)return;
	UKismetSystemLibrary::PrintString(this, "ValidatedCheckpoint!");

	const TArray<ACheckPoint*>& _checkpoints = raceSubSystem->GetCheckpoints();
	if (_checkpoints.Num() == 0)
		return;

	if (_checkpoints.IsValidIndex(currentCheckPointIndex))
	{
		ACheckPoint* _expectedCheckpoint = _checkpoints[currentCheckPointIndex];
		if (_expectedCheckpoint == _checkpoint)
		{
			currentCheckPointIndex++;

			if (currentCheckPointIndex >= _checkpoints.Num())
			{
				currentCheckPointIndex = 0;
				currentLap++;

				OnRep_CurrentLap();
				onLapCompleted.Broadcast(this);

				if (currentLap >= maxLap)
				{
					onRaceFinished.Broadcast(this);
					UKismetSystemLibrary::PrintString(this, "Race Finished !");
				}
				else
				{
					UKismetSystemLibrary::PrintString(this, "Lap Completed !");
				}
			}
			else
			{
				UKismetSystemLibrary::PrintString(this, "Checkpoint Validated !");
			}

			_checkpoint->OnCheckpointValidated().Broadcast(this, _checkpoint);
			// GetDashboardWidget()->UpdateCurrentLapsDashboard(currentLap);

		}
	}
}

UDashboardWidget* AKart::GetDashboardWidget() const
{
	return GetDashboardHUD()->GetCurrentDashboard();
}

ADashboard_HUD* AKart::GetDashboardHUD() const
{
	APlayerController* _playerController = Cast<APlayerController>(GetController());
	if (!_playerController) return nullptr;

	ADashboard_HUD* _HUD = Cast<ADashboard_HUD>(_playerController->GetHUD());

	return _HUD;
}


bool AKart::Server_ValidateCheckpoint_Validate(ACheckPoint* _checkpoint)
{
	return _checkpoint != nullptr;;
}

void AKart::OnRep_CurrentCheckpoint()
{
	UKismetSystemLibrary::PrintString(this, "Checkpoint chenged !");
}

void AKart::OnRep_CurrentLap()
{
	UKismetSystemLibrary::PrintString(this, TEXT("Lap changed !"));
	if (IsLocallyControlled())
	{
		if (UDashboardWidget* _dashboardWidget = GetDashboardWidget())
		{
			_dashboardWidget->UpdateCurrentLapsDashboard(currentLap);
		}
	}
}


void AKart::Server_ValidateCheckpoint_Implementation(ACheckPoint* _checkpoint)
{
	if (!_checkpoint)return;

	if (HasAuthority())
	{
		ValidateCheckpoint(_checkpoint);
	}
}




