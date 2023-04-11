// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstaclePool.h"

// Sets default values
AObstaclePool::AObstaclePool()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AObstaclePool::BeginPlay()
{
	Super::BeginPlay();
	// _pool = TArray<ABaseObstacle*>();
	SetFolderPath(FName(GetName()));
}

AObstacleBase* AObstaclePool::Create() const
{
	AActor* spawned = GetWorld()->SpawnActor(ObstacleTemplate);
	AObstacleBase* ret = Cast<AObstacleBase>(spawned);
	return ret;
}

AObstacleBase* AObstaclePool::Get()
{
	const int num = _pool.Num();

	AObstacleBase* ret;

	if (num <= 0)
	{
		ret = Create();
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
		ret->AttachToActor(this, rules);
		ret->SetFolderPath(FName(GetName()));
	}
	else
	{
		ret = _pool.Pop();
	}

	ret->SetActive(true);

	return ret;
}

void AObstaclePool::Return(AObstacleBase* obstacle)
{
	obstacle->Reset();
	obstacle->SetActive(false);
	_pool.Add(obstacle);
}
