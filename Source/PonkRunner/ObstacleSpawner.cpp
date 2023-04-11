// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
	//	using the TimerManager instead of Tick() for increased performance
	PrimaryActorTick.bCanEverTick = false;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = Area;
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	_timerManager = &GetWorld()->GetTimerManager();
	_obManager = Cast<AObstacleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AObstacleManager::StaticClass()));
	if (SpawningEnabled)
		ScheduleSpawn();
}

float AObstacleSpawner::GetIntervalTime() const
{
	return SpawnInterval + FMath::FRandRange(-SpawnIntervalRandomOffset, SpawnIntervalRandomOffset);
}

void AObstacleSpawner::SetSpawningEnabled(const bool enabled)
{
	SpawningEnabled = enabled;
	if (SpawningEnabled)
	{
		ScheduleSpawn();
	}
	else
	{
		_timerManager->ClearTimer(_timerHandle);
	}
}

void AObstacleSpawner::SpawnActor()
{
	UpdateSpawnPositionOrigin();
	const FVector SpawnPosition = GetRandomAreaPosition();
	_obManager->SpawnObstacle(&SpawnPosition);
}

void AObstacleSpawner::UpdateSpawnPositionOrigin()
{
	const float offsetFromAnchor = 1200.f;
	FVector anchor = _obManager->WorldAnchor->GetActorLocation();
	FVector position = FVector(anchor.X + offsetFromAnchor, 0.f, 0.f);
	SetActorLocation(position);
}

void AObstacleSpawner::ScheduleSpawn()
{
	const float Time = GetIntervalTime();
	_timerManager->SetTimer(_timerHandle, this, &AObstacleSpawner::SpawnActorScheduled, Time, false);
}

void AObstacleSpawner::SpawnActorScheduled()
{
	SpawnActor();
	if (SpawningEnabled)
		ScheduleSpawn();
}

FVector AObstacleSpawner::GetRandomAreaPosition() const
{
	FBoxSphereBounds bounds = Area->CalcBounds(GetActorTransform());
	FVector pos = bounds.Origin;
	pos.X += bounds.BoxExtent.X * (FMath::FRand() * 2.f - 1.f);
	pos.Y += bounds.BoxExtent.Y * (FMath::FRand() * 2.f - 1.f);
	pos.Z += bounds.BoxExtent.Z * (FMath::FRand() * 2.f - 1.f);
	return pos;
}
