#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"3C/Kart.h"
#include "Item.generated.h"

UCLASS(Abstract)
class MARIOKART_API AItem : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)TObjectPtr<UTexture2D> itemImage = nullptr;
	
public:	
	AItem();
	FORCEINLINE TObjectPtr<UTexture2D> GetItemImage() { return itemImage; }

public:
	virtual void Use(AKart* _targetKart) PURE_VIRTUAL(AItem::Use, );

};
