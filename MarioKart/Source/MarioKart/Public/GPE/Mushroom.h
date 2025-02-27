#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include "Mushroom.generated.h"

UCLASS()
class MARIOKART_API AMushroom : public AItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float boostValue = 150.0f;
	UPROPERTY(EditAnywhere) float boostTime = 3.0f;
	
public:	
	AMushroom();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Use(AKart* _targetKart)override;

};
