// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleBase.h"

AObstacleBase::AObstacleBase()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetBoxExtent(FVector(10.f, 350.f, 1.f));
	Collider->SetupAttachment(RootComponent);
}

void AObstacleBase::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AObstacleBase::OnColliderOverlapBegin);
}

void AObstacleBase::Reset()
{
	Super::Reset();
	IsAlive = true;
	KilledByPlayer = false;
}

void AObstacleBase::UpdateObstacle(float dt)
{
	FVector pos = GetActorLocation();
	pos.X -= Speed * dt;
	SetActorLocation(pos);
}

bool AObstacleBase::IsOutOfBounds(FVector const* runnerPosition) const
{
	constexpr float unitsBehindRunner = 300.f;
	return GetActorLocation().X < runnerPosition->X - unitsBehindRunner;
}

void AObstacleBase::OnColliderOverlapBegin(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
}

void AObstacleBase::Kill()
{
	IsAlive = false;
}

void AObstacleBase::OnHitByBullet()
{
	if (KillWhenHit)
	{
		KilledByPlayer = true;
		Kill();
	}
}
