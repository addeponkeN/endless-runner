// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnerBase.h"
#include "WallSpawner.generated.h"

/**
 * 
 */
UCLASS()
class PONKRUNNER_API AWallSpawner : public ASpawnerBase
{
	GENERATED_BODY()

public:
	AWallSpawner();

protected:
	virtual void BeginPlay() override;

	virtual void SpawnActor() override;

	virtual void SetSpawningEnabled(bool enabled) override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WallObstacleTemplate;

protected:
	UPROPERTY(EditAnywhere)
	AObstacleManager* _obManager;
};
