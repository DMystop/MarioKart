#include "GPE/RepellingWall.h"
#include "3C/Kart.h"
#include "Components/PrimitiveComponent.h"
#include <Kismet/KismetSystemLibrary.h>

ARepellingWall::ARepellingWall()
{
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
    mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    mesh->SetupAttachment(RootComponent);

	SetActorEnableCollision(true);
}

void ARepellingWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARepellingWall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    RepelPawn(DeltaTime);
}

void ARepellingWall::NotifyActorBeginOverlap(AActor* OtherActor)
{
    if (!OtherActor)return;

    AKart* _player = Cast<AKart>(OtherActor);
    if (_player && repelledPawn == nullptr)
    {
        repelledPawn = _player;
        startLocation = _player->GetActorLocation();

        FVector _wallLocation = GetActorLocation();
        repelDirection = (startLocation - _wallLocation).GetSafeNormal();
        repelDirection.Z = 0; 

        targetLocation = startLocation + (repelDirection * repelDistance);
        repelProgress = 0.0f; 
    }
}



void ARepellingWall::RepelPawn(float _delta)
{
    if (repelledPawn)
    {
        repelProgress += _delta * repelSpeed;

        if (repelProgress >= 1.0f) 
        {
            repelledPawn = nullptr;
        }
        else
        {
            FVector _newLocation = FMath::Lerp(startLocation, targetLocation, repelProgress);
            repelledPawn->SetActorLocation(_newLocation, true); 
        }
    }
}

