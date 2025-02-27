#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include "Mushroom.generated.h"

UCLASS()
class MARIOKART_API AMushroom : public AItem
{
	GENERATED_BODY()
	
public:	
	AMushroom();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
