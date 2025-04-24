#include "GPE/Goomba.h"
#include "Components/BillboardComponent.h"
#include "3C/StunComponentComponent.h"
#include <GPE/Item.h>
#include <Kismet/KismetMathLibrary.h>

AGoomba::AGoomba()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	goombaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoombaMesh"));
	goombaMesh->SetupAttachment(RootComponent);

	// Create patrol point A
	patrolPointA = CreateDefaultSubobject<UBillboardComponent>(TEXT("PatrolPointA"));
	patrolPointA->SetupAttachment(RootComponent);
	patrolPointA->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));

	// Create patrol point B
	patrolPointB = CreateDefaultSubobject<UBillboardComponent>(TEXT("PatrolPointB"));
	patrolPointB->SetupAttachment(RootComponent);
	patrolPointB->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
}

void AGoomba::BeginPlay()
{
	Super::BeginPlay();
	patrolPoints.Add(patrolPointA->GetComponentLocation());
	patrolPoints.Add(patrolPointB->GetComponentLocation());
}

void AGoomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (patrolPoints.Num() < 2) return;

	MoveToTarget(DeltaTime);
	CheckSwitchTarget();
}

void AGoomba::MoveToTarget(float DeltaTime)
{
	FVector _currentTarget = patrolPoints[currentTargetIndex];
	FVector _toTarget = _currentTarget - GetActorLocation();
	FVector _direction = _toTarget.GetSafeNormal2D();

	SetActorRotation(FRotator(0.f, _direction.Rotation().Yaw, 0.f));

	FVector _forward = GetActorLocation() + GetActorForwardVector() * moveSpeed;
	FVector _newPos = UKismetMathLibrary::VInterpTo_Constant(GetActorLocation(), _forward, DeltaTime, FMath::Abs(moveSpeed));

	SetActorLocation(_newPos);
}


void AGoomba::CheckSwitchTarget()
{
	FVector _currentTarget = patrolPoints[currentTargetIndex];
	float _distance = FVector::Dist2D(GetActorLocation(), _currentTarget);

	if (_distance <= switchDistance)
	{
		SwitchTarget();
	}
}

void AGoomba::SwitchTarget()
{
	currentTargetIndex = (currentTargetIndex + 1) % patrolPoints.Num();
}


void AGoomba::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGoomba::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor) return;

	AItem* _otherItem = Cast<AItem>(OtherActor);
	AKart* _kart = Cast<AKart>(OtherActor);
	if (_otherItem)
	{
		_otherItem->Destroy();
		return;
	}
	else if (_kart)
	{
		UStunComponent* _stun = _kart->GetComponentByClass<UStunComponent>();
		if (!_stun)return;
		_stun->Stun();
		return;
	}
}
