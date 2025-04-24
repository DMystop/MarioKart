#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemBoxSubSystem.generated.h"

class AMysteryItemBox;

UCLASS()
class MARIOKART_API UItemBoxSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY() TArray<TObjectPtr<AMysteryItemBox>> activeItemBoxes;
	float time = 5.0f;

public:
	void RegisterItemBox(AMysteryItemBox* _box);
	void OnItemBoxDestroyed(FVector _location);

private:
	void RespawnItemBox(FVector _location);
	
};
