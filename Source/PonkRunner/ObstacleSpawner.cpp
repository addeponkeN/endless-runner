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
	_timerManager = &GetWorld()->GetTimerManager();
	_obManager = Cast<AObstacleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AObstacleManager::StaticClass()));
	Super::BeginPlay();
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
	const FVector SpawnPosition = GetRandomAreaPosition();
	ABaseObstacle* obstacle = _obManager->SpawnObstacle();
	obstacle->SetActorLocation(SpawnPosition);
	// GetWorld()->SpawnActor(ActorToSpawn, &SpawnPosition);
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
