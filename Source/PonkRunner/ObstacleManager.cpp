// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleManager.h"

#include "ActorPool.h"
#include "PonkRunnerGameModeBase.h"

// Sets default values
AObstacleManager::AObstacleManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AObstacleManager::BeginPlay()
{
	Super::BeginPlay();
	ActorPool<AObstacleBase>::Init(GetWorld(), ObstacleTemplate);

	auto baseGameMode = GetWorld()->GetAuthGameMode();
	auto gameMode = Cast<APonkRunnerGameModeBase>(baseGameMode);
	auto gameMode2 = dynamic_cast<APonkRunnerGameModeBase*>(baseGameMode);
	WorldAnchor = gameMode->WorldAnchor;
	WorldAnchor = gameMode2->WorldAnchor;
}

void AObstacleManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ActorPool<AObstacleBase>::Clear();
}

// Called every frame
void AObstacleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

AObstacleBase* AObstacleManager::SpawnObstacle(FVector const* position)
{
	AObstacleBase* obstacle = ActorPool<AObstacleBase>::Spawn(position);
	_obstacles.Add(obstacle);
	return obstacle;
}

void AObstacleManager::DespawnObstacle(AObstacleBase* obstacle)
{
	_obstacles.Remove(obstacle);
	ActorPool<AObstacleBase>::Return(obstacle);
}
