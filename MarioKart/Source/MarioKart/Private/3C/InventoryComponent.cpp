// Fill out your copyright notice in the Description page of Project Settings.


#include "3C/InventoryComponent.h"
#include "GPE/Item.h"
#include <Dashboard_HUD.h>
#include"Kismet/KismetSystemLibrary.h"


void UInventoryComponent::AddCoin(const int _count)
{
	coinCount = (coinCount + _count > 10) ? 10 : coinCount + _count;
	APlayerController* _playerController = GetWorld()->GetFirstPlayerController();
	if (!_playerController) return;
	ADashboard_HUD* _dashboardHUD = Cast<ADashboard_HUD>(_playerController->GetHUD());
	if (!_dashboardHUD) return;
	TObjectPtr<UDashboardWidget> _dashboardWidget = _dashboardHUD->GetCurrentDashboard();
	if (!_dashboardWidget) return;
	_dashboardWidget->UpdateCoinDashboard(coinCount);
}


UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts	
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	UpdateItemDashboard();
}



// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(TSubclassOf<AItem> _item)
{
	if (items.Num() > 2) return;
	items.Add(_item);
	UpdateItemDashboard();
}


void UInventoryComponent::UseItem(const FInputActionValue& _value)
{
	UKismetSystemLibrary::PrintString(this, "Use");
	if (items.IsEmpty() || !canUse)return;
	AKart* _owner = Cast<AKart>(GetOwner());
	if (GetOwner()->HasAuthority())
	{
		FActorSpawnParameters _spawnParams;
		_spawnParams.Owner = _owner;
		_spawnParams.Instigator = Cast<APawn>(_owner);
		_spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		//AItem* _item = GetWorld()->SpawnActor<AItem>(items[0], GetOwner()->GetTransform() ,_spawnParams);
		FVector _spawnLoc = FVector(_owner->GetActorLocation().X + 450.0f, _owner->GetActorLocation().Y, _owner->GetActorLocation().Z);
		AItem* _item = GetWorld()->SpawnActor<AItem>(items[0], _spawnLoc, _owner->GetActorRotation(), _spawnParams);
		if (_item)
		{
			_item->Use(_owner);
		}
	}
	else
	{
		onUse.Broadcast(items[0], _owner);
	}
	items.RemoveAt(0);
	UpdateItemDashboard();
}

void UInventoryComponent::SetCanUseOnStun(bool _isStun)
{
	canUse = !_isStun;
}

UDashboardWidget* UInventoryComponent::GetDashboardWidget() const
{
	APlayerController* _playerController = GetWorld()->GetFirstPlayerController();
	if (!_playerController) return nullptr;

	ADashboard_HUD* _dashboardHUD = Cast<ADashboard_HUD>(_playerController->GetHUD());
	if (!_dashboardHUD) return nullptr;

	return _dashboardHUD->GetCurrentDashboard();
}


void UInventoryComponent::UpdateItemDashboard()
{
	GetDashboardWidget()->UpdateItemsDashboard(items);
}

void UInventoryComponent::UpdateCoinDashboard()
{
	GetDashboardWidget()->UpdateItemsDashboard(items);
}
