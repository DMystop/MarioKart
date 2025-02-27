#include "GPE/Carapace.h"
#include "3C/Kart.h"
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
	if (!canMove)return;
	Move(DeltaTime);
	Rotate(DeltaTime);

}

void ACarapace::Use(AKart* _targetKart)
{
	//if (!_targetKart) return;

	////get the shoot dir
	//int _shootDirection = _targetKart->GetShootDirection();
	//// Place carapace in front or behind
	//FVector _spawnLocation = _targetKart->GetActorLocation() + _targetKart->GetActorForwardVector() * 100.0f * _shootDirection;
	//SetActorLocation(_spawnLocation);
	//// orientation
	//SetActorRotation(_targetKart->GetActorRotation());
	//if (_shootDirection == -1)
	//{
	//	// if shoot behind, inverse move dir
	//	SetActorRotation(GetActorRotation() + FRotator(0, 180, 0));
	//}

	//mesh->IgnoreActorWhenMoving(_targetKart, true);
	//dir = _shootDirection;
	//canMove = true;


	//TODO IN THE KART
	/*UPROPERTY(EditAnywhere)int shootDirection = 1;
	FORCEINLINE int GetShootDirection() const { return shootDirection; }

	void ToggleShootDirection(const FInputActionValue& _value)
	{
		shootDirection *= -1
	}*/
}

void ACarapace::Rotate(float _delta)
{
	FQuat _rotationDelta = FQuat(FRotator(0.f, rotationSpeed * _delta, 0.f));
	mesh->AddLocalRotation(_rotationDelta, false, nullptr, ETeleportType::None);
}


void ACarapace::Move(float _delta)
{
	FVector _newLocation = GetActorLocation() + (GetActorForwardVector() * moveSpeed * _delta * dir);
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
	AKart* _kart = Cast<AKart>(OtherActor);
	if (_otherItem)
	{
		_otherItem->Destroy();
		Destroy();
		return;
	}
	else if (_kart)
	{
		//TODO STUN
		Destroy();
		return;
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

