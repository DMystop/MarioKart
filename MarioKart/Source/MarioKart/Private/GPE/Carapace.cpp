#include "GPE/Carapace.h"

ACarapace::ACarapace()
{
	PrimaryActorTick.bCanEverTick = true;

	movement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	movement->InitialSpeed = 1200.0f;
	movement->MaxSpeed = 1200.0f;
	movement->bShouldBounce = true;
	movement->Bounciness = 0.8f;
	movement->Friction = 0.2f;
	movement->ProjectileGravityScale = 0.0f; 

	mesh->SetSimulatePhysics(true);
	//mesh->SetCollisionProfileName("BlockAll");

}

void ACarapace::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACarapace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate(DeltaTime);

}

void ACarapace::Rotate(float _delta)
{
	FQuat _rotationDelta = FQuat(FRotator(0.f, rotationSpeed * _delta, 0.f));
	AddActorLocalRotation(_rotationDelta, false, nullptr, ETeleportType::None);
}

void ACarapace::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (!OtherActor) return;
	//if otherActor = Cast<AKartPawn> => stun => destroy


}

void ACarapace::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	currentBounces++;
	if (currentBounces >= maxBounces)
	{
		Destroy();
	}
}

