#include "3C/InventoryComponent.h"
#include "GPE/Item.h"
#include <Dashboard_HUD.h>
#include"Kismet/KismetSystemLibrary.h"


void UInventoryComponent::AddCoin(const int _count)
{
	int _newCoinCount = coinCount + _count;

	coinCount = FMath::Clamp(_newCoinCount, 0, maxCoinCount);

	if (UDashboardWidget* _dashboard = GetDashboardWidget())
	{
		_dashboard->UpdateCoinDashboard(coinCount);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Dashboard widget not found while modifying coin count."));
	}
}



UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	UpdateItemDashboard();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddItem(TSubclassOf<AItem> _item)
{
	if (items.Num() >= 2) return;
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
	APlayerController* _playerController = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
	if (!_playerController) return nullptr;

	ADashboard_HUD* _HUD = Cast<ADashboard_HUD>(_playerController->GetHUD());
	if (!_HUD) return nullptr;
	return _HUD->GetCurrentDashboard();
}


void UInventoryComponent::UpdateItemDashboard()
{
	if (UDashboardWidget* _dashboard = GetDashboardWidget())
		_dashboard->UpdateItemsDashboard(items);
}


void UInventoryComponent::UpdateCoinDashboard()
{
	if (UDashboardWidget* _dashboard = GetDashboardWidget())
		_dashboard->UpdateItemsDashboard(items);
}

