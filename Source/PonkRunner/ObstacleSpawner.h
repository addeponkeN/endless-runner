// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SpawnerBase.h"
#include "GameFramework/Actor.h"

#include "ObstacleSpawner.generated.h"

UCLASS()
class PONKRUNNER_API AObstacleSpawner : public ASpawnerBase
{
	GENERATED_BODY()

public:
	AObstacleSpawner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SpawnActor() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ObstacleTemplate;

protected:
	UPROPERTY(EditAnywhere)
	AObstacleManager* _obManager;
	
private:
	FVector GetRandomAreaPosition() const;
	
};
