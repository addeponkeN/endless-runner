// Fill out your copyright notice in the Description page of Project Settings.


#include "RunManCharacter.h"

#include "ObstacleBase.h"
#include "PonkRunner.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

ARunManCharacter::ARunManCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent* capsuleComponent = GetCapsuleComponent();

	RunnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RunnerMesh->SetupAttachment(capsuleComponent);

	RunnerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RunnerCamera->SetupAttachment(capsuleComponent);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(capsuleComponent);

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	AddOwnedComponent(Health);
}

void ARunManCharacter::BeginPlay()
{
	Super::BeginPlay();

	// WeaponController = Cast<UWeaponController>(GetComponentByClass(UWeaponController::StaticClass()));

	RunPlayerController = Cast<ARunnerPlayerController>(GetController());
	DisableInput(RunPlayerController);

	//	setup HUD
	if (HUDClass)
	{
		HUD = CreateWidget<URunnerHUD>(RunPlayerController, HUDClass);
		check(HUD);
		HUD->AddToPlayerScreen();
		HUD->SetVisibility(ESlateVisibility::Hidden);
	}

	// const FVector startPosition = FVector(0.f, 0.f, 10.f);
	// SetActorLocation(startPosition);

	ResetRunMan();

	if (Collider)
	{
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ARunManCharacter::OnColliderOverlapBegin);
		LOG("listening to ObstacleCollider");
	}

	Health->OnValueChangedEvent.AddDynamic(this, &ARunManCharacter::OnHealthChanged);
	// OnHealthChanged();
}

void ARunManCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//	not sure if this is needed...
	if (HUD)
	{
		HUD->RemoveFromParent();
		HUD = nullptr;
	}
}

void ARunManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// HACK: had no effect when doing this in BeginPlay(), so im setting it here instead...
	SetActorRotation(FRotator::ZeroRotator);

	if (_direction > 0.f || _direction < 0.f)
	{
		MoveHorizontalRelativeToActor(DeltaTime);
	}

	// move forward
	// AddMovementInput(GetActorForwardVector(), MoveSpeed * DeltaTime);
}

void ARunManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &ARunManCharacter::MoveHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Jump"), this, &ARunManCharacter::RunManJump);
}

void ARunManCharacter::ResetRunMan()
{
	const FVector startPosition = FVector(0.f, 0.f, 10.f);
	SetActorLocation(startPosition);

	_direction = 0.f;

	Health->ResetHealth();

	OnHealthChanged();
}

void ARunManCharacter::RunManJump(float v)
{
	if (v > 0.f)
	{
		Super::Jump();
	}
}

void ARunManCharacter::OnColliderOverlapBegin(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (AObstacleBase* obs = Cast<AObstacleBase>(OtherActor))
	{
		Health->Damage(1.f);
		obs->Kill();
	}
}

void ARunManCharacter::OnHealthChanged()
{
	HUD->SetHealth(Health->Value);
}

void ARunManCharacter::MoveHorizontal(float direction)
{
	_direction = direction;
}

void ARunManCharacter::MoveHorizontalRelativeToActor(float dt)
{
	AddMovementInput(GetActorRightVector(), _direction * MoveSpeed * dt);
}
