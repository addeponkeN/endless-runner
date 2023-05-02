// Fill out your copyright notice in the Description page of Project Settings.


#include "RunManCharacter.h"

#include "ObstacleBase.h"
#include "PonkRunner.h"
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
}

void ARunManCharacter::BeginPlay()
{
	Super::BeginPlay();

	// WeaponController = Cast<UWeaponController>(GetComponentByClass(UWeaponController::StaticClass()));

	//	setup HUD
	// if (HUDClass)
	// {
	// HUD = CreateWidget<URunnerHUD>(RunPlayerController, HUDClass);
	// check(HUD);
	// HUD->AddToPlayerScreen();
	// HUD->SetVisibility(ESlateVisibility::Hidden);
	// }

	// const FVector startPosition = FVector(0.f, 0.f, 10.f);
	// SetActorLocation(startPosition);

	ResetRunMan();

	if (Collider)
	{
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ARunManCharacter::OnColliderOverlapBegin);
		// LOG("listening to ObstacleCollider");
	}

	Health->OnValueChangedEvent.AddDynamic(this, &ARunManCharacter::OnHealthChanged);
	// OnHealthChanged();
}

void ARunManCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//	not sure if this is needed...
	// if (HUD)
	// {
	// HUD->RemoveFromParent();
	// HUD = nullptr;
	// }
}

void ARunManCharacter::FinalizeCharacter()
{
	RunPlayerController = Cast<ARunnerPlayerController>(GetController());
	DisableInput(RunPlayerController);

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
		input->BindAxis(TEXT("P2_MoveHorizontal"), this, &ARunManCharacter::P2_MoveHorizontal);
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
	// HUD->SetHealth(Health->Value);
}

void ARunManCharacter::P1_MoveHorizontal(float direction)
{
	_direction = direction;
	if (direction != 0.f)
	{
		LOG(FString::Printf(TEXT("P%i moving"), PlayerIndex));
	}
}

void ARunManCharacter::P2_MoveHorizontal(float direction)
{
	OtherRunner->_direction = direction;
	if (direction != 0.f)
	{
		LOG(FString::Printf(TEXT("P%i moving"), OtherRunner->PlayerIndex));
	}
}

void ARunManCharacter::MoveHorizontalRelativeToActor(float dt)
{
	AddMovementInput(GetActorRightVector(), _direction * MoveSpeed * dt);
}

