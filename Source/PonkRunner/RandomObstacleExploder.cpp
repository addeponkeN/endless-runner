// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomObstacleExploder.h"

#include "PonkRunner.h"
#include "WallObstacle.h"

URandomObstacleExploder::URandomObstacleExploder()
{
	PrimaryComponentTick.bCanEverTick = false;

	auto owner = GetOwner();
	if (owner && !owner->IsA(AObstacleManager::StaticClass()))
	{
		LOGE("RandomObstacleExploder can only be attached to an ObstacleManager")
		DestroyComponent();
		return;
	}
}


void URandomObstacleExploder::BeginPlay()
{
	Super::BeginPlay();

	ObstacleManager = GetOwner<AObstacleManager>();
	ObstacleManager->OnObstacleOutOfBoundsEvent.
	                 AddDynamic(this, &URandomObstacleExploder::RollAndExplodeRandomObstacle);
}

void URandomObstacleExploder::RollAndExplodeRandomObstacle(AObstacleBase* obstacle)
{
	TArray<AObstacleBase*> obstacles = ObstacleManager->GetObstacles();

	int32 obstacleCount = obstacles.Num();
	if (obstacleCount <= 0)
		return;

	const float roll = FMath::FRand();

	if (ExplodeChance > roll)
	{
		const int32 rndObstacleIndex = FMath::RandRange(0, obstacleCount - 1);
		AObstacleBase* rndObstacle = obstacles[rndObstacleIndex];

		//	dont explode non-killable obstacles
		if (!rndObstacle->KillWhenHit)
			return;

		//	explode boom bang
		rndObstacle->Kill();
		// LOG("boom");
	}
}
