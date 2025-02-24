#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS(Abstract)
class MARIOKART_API AItem : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	
public:	
	AItem();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
