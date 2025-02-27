#include "GPE/Carapace.h"
#include <Kismet/KismetSystemLibrary.h>

ACarapace::ACarapace()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
}

void ACarapace::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACarapace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
	Rotate(DeltaTime);

}

void ACarapace::Rotate(float _delta)
{
	FQuat _rotationDelta = FQuat(FRotator(0.f, rotationSpeed * _delta, 0.f));
	mesh->AddLocalRotation(_rotationDelta, false, nullptr, ETeleportType::None);
}


void ACarapace::Move(float _delta)
{
	FVector _newLocation = GetActorLocation() + (GetActorForwardVector() * moveSpeed * _delta);
	SetActorLocation(_newLocation);
}

void ACarapace::Collision()
{
	FVector _currentVelocity = GetActorForwardVector() * moveSpeed;
	FVector _newDirection = -_currentVelocity.GetSafeNormal();
	SetActorRotation(_newDirection.Rotation());
	currentBounces++;
	if (currentBounces >= maxBounces)
	{
		Destroy();
	}
}

void ACarapace::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor) return;
	
	//TODO if otherActor = Cast<AKartPawn> => stun => destroy

	AItem* _otherItem = Cast<AItem>(OtherActor);
	if (_otherItem)
	{
		_otherItem->Destroy();
		Destroy();
	}
	Collision();

}

void ACarapace::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	/*currentBounces++;
	UKismetSystemLibrary::PrintString(this, "Bounce");
	if (currentBounces >= maxBounces)
	{
		Destroy();
		return;
	}
	FVector _currentVelocity = GetVelocity();
	FVector _reflectedVelocity = FMath::GetReflectionVector(_currentVelocity, HitNormal);
	SetActorRotation(_reflectedVelocity.Rotation());
	FVector _newVelocity = _reflectedVelocity.GetSafeNormal() * moveSpeed;
	GetRootComponent()->ComponentVelocity = _newVelocity;*/
}

