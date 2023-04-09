// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleManager.h"

#include "ActorPool.h"

// Sets default values
AObstacleManager::AObstacleManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_obstacles = TArray<ABaseObstacle*>();
	_index = 0;
}

// Called when the game starts or when spawned
void AObstacleManager::BeginPlay()
{
	Super::BeginPlay();

	ActorPool<ABaseObstacle>::Init(GetWorld(), ObstacleTemplate);
	
	// if (!Pool)
	// {
	// LOG("Pool null #1");
	// auto world = GetWorld();
	// Pool = Cast<Pool<ABaseObstacle>>(UGameplayStatics::GetActorOfClass(world, Pool<ABaseObstacle>::StaticClass()));
	// if (!Pool)
	// {
	// LOG("Pool null #2");
	// Pool = Cast<Pool<ABaseObstacle>>(world->SpawnActor(Pool<ABaseObstacle>::StaticClass()));
	// Pool->ObjectTemplate = ObstacleTemplate;
	// }
	// }
}

// Called every frame
void AObstacleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int32 size = _obstacles.Num();
	for (int i = 0; i < size; ++i)
	{
		FVector location = _obstacles[i]->GetActorLocation();
		if (location.X < -30)
		{
			DespawnObstacle(_obstacles[i]);
			i--;
			size--;
		}
	}
}

ABaseObstacle* AObstacleManager::SpawnObstacle()
{
	ABaseObstacle* obstacle = ActorPool<ABaseObstacle>::Get();
	_obstacles.Add(obstacle);
	return obstacle;
}

void AObstacleManager::DespawnObstacle(ABaseObstacle* obstacle)
{
	_obstacles.Remove(obstacle);
	ActorPool<ABaseObstacle>::Return(obstacle);
}
