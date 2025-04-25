#include "GPE/RespawnComponent.h"

URespawnComponent::URespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void URespawnComponent::BeginPlay()
{
	Super::BeginPlay();
}


void URespawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void URespawnComponent::HandleTaken()
{
	UStaticMeshComponent* _mesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	_mesh->SetVisibility(false);

	originalCollision = _mesh->GetCollisionEnabled();
	_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorld()->GetTimerManager().SetTimer(respawnTimerHandle, this, &URespawnComponent::Respawn, respawnTime, false);
}

void URespawnComponent::Respawn()
{
	UStaticMeshComponent* _mesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	_mesh->SetVisibility(true);
	_mesh->SetCollisionEnabled(originalCollision);
}

