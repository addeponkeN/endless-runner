// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerBase.h"

#include "ObstacleManager.h"

ASpawnerBase::ASpawnerBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = Area;
}

void ASpawnerBase::BeginPlay()
{
	Super::BeginPlay();
	_timerManager = &GetWorld()->GetTimerManager();
	if (SpawningEnabled)
		ScheduleSpawn();
}

float ASpawnerBase::GetIntervalTime() const
{
	return FMath::Lerp(SpawnIntervalMax, SpawnIntervalMin, Difficulty)
		+ FMath::FRandRange(-SpawnIntervalRandomOffset, SpawnIntervalRandomOffset);
}

void ASpawnerBase::SetSpawningEnabled(const bool enabled)
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

void ASpawnerBase::SpawnActor()
{
}

void ASpawnerBase::ScheduleSpawn()
{
	const float Time = GetIntervalTime();
	_timerManager->SetTimer(_timerHandle, this, &ASpawnerBase::SpawnActorScheduled, Time, false);
}

void ASpawnerBase::SpawnActorScheduled()
{
	SpawnActor();
	if (SpawningEnabled)
		ScheduleSpawn();
}
