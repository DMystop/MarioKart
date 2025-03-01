#include "GPE/Banana.h"
#include "3C/Kart.h"

ABanana::ABanana()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
}

void ABanana::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABanana::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABanana::Use(AKart* _targetKart)
{
	if (!_targetKart) return;

	bool _shootDirection = _targetKart->GetShootDirection();
	FVector _dir = _targetKart->GetActorForwardVector() * 100.0f;
	_dir = _shootDirection ? -_dir : _dir;
	FVector _spawnLocation = _targetKart->GetActorLocation() +_dir ;
	SetActorLocation(_spawnLocation);
}

void ABanana::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor)return;

	//TODO Player
}

