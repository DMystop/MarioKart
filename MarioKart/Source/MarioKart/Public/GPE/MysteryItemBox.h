#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MysteryItemBox.generated.h"

class AItem;
class URespawnComponent;
UCLASS()
class MARIOKART_API AMysteryItemBox : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<URespawnComponent> respawnComponent = nullptr;

	UPROPERTY(EditAnywhere)float rotationSpeed = 250.0f;
	UPROPERTY(EditAnywhere)float levitateSpeed = 2.0f;
	UPROPERTY(EditAnywhere)float levitateAmplitude = 40.0f;
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AItem>> availablesItems;
	UPROPERTY() TSubclassOf<AItem> mushroomClass;
	UPROPERTY() TSubclassOf<AItem> carapaceClass;
	UPROPERTY() TSubclassOf<AItem> bananaClass;
	float runningTime = 0.0f;
	//UPROPERTY(EditAnywhere)float respawnTime = 5.0f; 
	//FTimerHandle respawnTimerHandle;


private:
	FORCEINLINE bool IsValidItemArray()
	{
		return availablesItems.Num() > 0;
	}

public:
	AMysteryItemBox();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Init();
	void Levitate(float _delta);
	void Rotate(float _delta);
	TSubclassOf<AItem> GiveRandomItem();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//void HandleTaken();
	//void Respawn();

};
