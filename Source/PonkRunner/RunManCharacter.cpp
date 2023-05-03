// Fill out your copyright notice in the Description page of Project Settings.


#include "RunManCharacter.h"

#include "ObstacleBase.h"
#include "PonkRunner.h"
#include "WeaponController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

ARunManCharacter::ARunManCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	UCapsuleComponent* capsuleComponent = GetCapsuleComponent();

	RunnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RunnerMesh->SetupAttachment(capsuleComponent);

	RunnerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RunnerCamera->SetupAttachment(capsuleComponent);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(capsuleComponent);

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	AddOwnedComponent(Health);

	WeaponController = CreateDefaultSubobject<UWeaponController>(TEXT("WeaponController"));
	AddOwnedComponent(WeaponController); 
}

void ARunManCharacter::BeginPlay()
{
	Super::BeginPlay();

	ResetRunMan();

	if (Collider)
	{
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ARunManCharacter::OnColliderOverlapBegin);
	}

	Health->OnValueChangedEvent.AddDynamic(this, &ARunManCharacter::OnHealthChanged);
}

void ARunManCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ARunManCharacter::FinalizeCharacter()
{
	RunPlayerController = Cast<ARunnerPlayerController>(GetController());
	DisableInput(RunPlayerController);

	if (HudTemplate)
	{
		Hud = CreateWidget<URunnerHUD>(RunPlayerController, HudTemplate);
		check(Hud);
		Hud->AddToPlayerScreen();
		Hud->SetVisibility(ESlateVisibility::Hidden);
		OnHealthChanged();
	}

	if (RunPlayerController)
	{
		ULocalPlayer* local = RunPlayerController->GetLocalPlayer();
		if (local)
		{
			PlayerIndex = local->GetLocalPlayerIndex();
		}
	}

	UInputComponent* input = Cast<UInputComponent>(GetComponentByClass(UInputComponent::StaticClass()));

	if (PlayerIndex == 0)
	{
		//	HACK: player1 controls both p1 & p2
		input->BindAxis(TEXT("P1_MoveHorizontal"), this, &ARunManCharacter::P1_MoveHorizontal);
		input->BindAction(TEXT("P1_Fire"), IE_Pressed, this, &ARunManCharacter::P1_Fire);
		input->BindAction(TEXT("P1_Fire"), IE_Released, this, &ARunManCharacter::P1_FireRelease);

		input->BindAxis(TEXT("P2_MoveHorizontal"), this, &ARunManCharacter::P2_MoveHorizontal);
		input->BindAction(TEXT("P2_Fire"), IE_Pressed, this, &ARunManCharacter::P2_Fire);
		input->BindAction(TEXT("P2_Fire"), IE_Released, this, &ARunManCharacter::P2_FireRelease);
	}
}

void ARunManCharacter::UpdateRunner(float dt)
{
	// HACK: had no effect when doing this in BeginPlay(), so im setting it here instead...
	SetActorRotation(FRotator::ZeroRotator);

	if (_direction > 0.f || _direction < 0.f)
	{
		MoveHorizontalRelativeToActor(dt);
	}
}

void ARunManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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
	if (Hud)
	{
		Hud->SetHealth(Health->Value);
	}
}

void ARunManCharacter::MoveHorizontalRelativeToActor(float dt)
{
	AddMovementInput(GetActorRightVector(), _direction * MoveSpeed * dt);
}

//	2 player, 1 keyboard band aid

void ARunManCharacter::P1_Fire()
{
	WeaponController->Fire();
}

void ARunManCharacter::P1_FireRelease()
{
	WeaponController->FireRelease();
}

void ARunManCharacter::P2_Fire()
{
	OtherRunner->WeaponController->Fire();
}

void ARunManCharacter::P2_FireRelease()
{
	OtherRunner->WeaponController->FireRelease();
}

void ARunManCharacter::P1_MoveHorizontal(float direction)
{
	_direction = direction;
}

void ARunManCharacter::P2_MoveHorizontal(float direction)
{
	OtherRunner->_direction = direction;
}
