// Fill out your copyright notice in the Description page of Project Settings.


#include "3C/Kart.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include"3C/KartMovementComponent.h"

// Sets default values
AKart::AKart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	arm = CreateDefaultSubobject<USpringArmComponent>("Spring");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");


	movement = CreateDefaultSubobject<UKartMovementComponent>("Movemnt");

	arm->SetupAttachment(RootComponent);
	camera->SetupAttachment(arm);
	mesh->SetupAttachment(RootComponent);

	AddOwnedComponent(movement);


}

// Called when the game starts or when spawned
void AKart::BeginPlay()
{
	Super::BeginPlay();
	InitInput();
	
}

// Called every frame
void AKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* _input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	_input->BindAction(input.accelerateAction, ETriggerEvent::Triggered, movement.Get(), &UKartMovementComponent::Accelerate);
	_input->BindAction(input.accelerateAction, ETriggerEvent::Completed, movement.Get(), &UKartMovementComponent::SetAddVelocity);
	_input->BindAction(input.brakeAction, ETriggerEvent::Triggered, movement.Get(), &UKartMovementComponent::Brake);
	_input->BindAction(input.brakeAction, ETriggerEvent::Completed, movement.Get(), &UKartMovementComponent::SetAddVelocity);
	_input->BindAction(input.turnAction, ETriggerEvent::Triggered, movement.Get(), &UKartMovementComponent::Rotate);
	_input->BindAction(input.turnAction, ETriggerEvent::Completed, movement.Get(), &UKartMovementComponent::Rotate);

}

void AKart::InitInput()
{
	ULocalPlayer* _local = GetWorld()->GetFirstLocalPlayerFromController();

	UEnhancedInputLocalPlayerSubsystem* _inputSystem = _local->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	_inputSystem->AddMappingContext(input.mappingContext, 0);
}

