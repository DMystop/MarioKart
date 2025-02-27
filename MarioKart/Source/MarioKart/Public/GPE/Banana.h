#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Item.h"
#include "Banana.generated.h"

UCLASS()
class MARIOKART_API ABanana : public AItem
{
	GENERATED_BODY()
	
public:	
	ABanana();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
