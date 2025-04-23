#include "GPE/ItemBoxSubSystem.h"
#include "GPE/MysteryItemBox.h"

void UItemBoxSubSystem::RegisterItemBox(AMysteryItemBox* _box)
{
	if (!_box)return;

	activeItemBoxes.Add(_box);
}

void UItemBoxSubSystem::OnItemBoxDestroyed(FVector _location)
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	FTimerHandle _respawnTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_respawnTimerHandle, FTimerDelegate::CreateUObject(this, &UItemBoxSubSystem::RespawnItemBox, _location), time, false);
}

void UItemBoxSubSystem::RespawnItemBox(FVector _location)
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	FActorSpawnParameters _spawnParams;
	_spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMysteryItemBox* _newBox = GetWorld()->SpawnActor<AMysteryItemBox>(AMysteryItemBox::StaticClass(), _location, FRotator::ZeroRotator, _spawnParams);

	if (_newBox)
	{
		RegisterItemBox(_newBox);
	}
}
