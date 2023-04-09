// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
	
	RunnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RunnerMesh->SetupAttachment(capsuleComponent);

	RunnerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RunnerCamera->SetupAttachment(capsuleComponent);
}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	FVector startPosition = FVector(0.f, 0.f, 10.f);
	SetActorLocation(startPosition);

	// somehow this does nothing when doing in BeginPlay() or the constructor, so im setting it in Tick() instead...
	//SetActorRotation(FRotator::ZeroRotator);
}

// Called every frame
void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// HACK: had no effect when doing this in BeginPlay() (L:31), so im setting it here instead...
	SetActorRotation(FRotator::ZeroRotator);
	// --
	
	if (_direction > 0.f || _direction < 0.f)
	{
		MoveHorizontalRelativeToActor(DeltaTime);
	}
}

// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &ARunnerCharacter::MoveHorizontal);
}

void ARunnerCharacter::MoveHorizontal(float direction)
{
	_direction = direction;
}

void ARunnerCharacter::MoveHorizontalRelativeToActor(float dt)
{
	AddMovementInput(GetActorRightVector(), _direction * MoveSpeed * dt);
}
