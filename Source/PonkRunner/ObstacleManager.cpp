// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleManager.h"

#include "ActorPool.h"
#include "PonkRunner.h"
#include "PonkRunnerGameModeBase.h"
#include "WallObstacle.h"

AObstacleManager::AObstacleManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AObstacleManager::BeginPlay()
{
	Super::BeginPlay();
	auto baseGameMode = GetWorld()->GetAuthGameMode();
	auto gameMode = Cast<APonkRunnerGameModeBase>(baseGameMode);
	auto gameMode2 = dynamic_cast<APonkRunnerGameModeBase*>(baseGameMode);
	WorldAnchor = gameMode->RunMan;
	WorldAnchor = gameMode2->RunMan;

	// if (!WorldAnchor)
	// {
		// LOG("anchor NULL");
	// }
}

void AObstacleManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ActorPool<AObstacleBase>::Clear();
}

void AObstacleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!WorldAnchor)
	{
		auto baseGameMode = GetWorld()->GetAuthGameMode();
		auto gameMode = Cast<APonkRunnerGameModeBase>(baseGameMode);
		auto gameMode2 = dynamic_cast<APonkRunnerGameModeBase*>(baseGameMode);
		WorldAnchor = gameMode->RunMan;
		WorldAnchor = gameMode2->RunMan;
		if (!WorldAnchor)
		{
			LOG("anchor NULL STILL");
		}
		else
		{
			LOG("anchor fixed");
		}
		return;
	}
	FVector endOfLine = WorldAnchor->GetActorLocation();

	for (int i = 0; i < _obstacles.Num(); ++i)
	{
		AObstacleBase* obstacle = _obstacles[i];

		obstacle->UpdateObstacle(DeltaTime);

		if (!obstacle->IsAlive || obstacle->IsOutOfBounds(&endOfLine))
		{
			DespawnObstacle(obstacle);
			i--;
		}
	}
}

void AObstacleManager::DespawnObstacle(AObstacleBase* obstacle)
{
	_obstacles.Remove(obstacle);

	if(obstacle->KilledByPlayer)
	{
		OnObstacleKilledEvent.Broadcast();
	}

	//	temporary band-aid
	if (AWallObstacle* wall = Cast<AWallObstacle>(obstacle))
	{
		ActorPool<AWallObstacle>::Return(wall);
	}
	else
	{
		ActorPool<AObstacleBase>::Return(obstacle);
	}
}

void AObstacleManager::ClearObstacles()
{
	int32 i = _obstacles.Num() - 1;
	while (_obstacles.Num() > 0)
	{
		DespawnObstacle(_obstacles[i--]);
	}
}
