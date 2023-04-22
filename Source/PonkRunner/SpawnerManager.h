// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnerBase.h"
#include "GameFramework/Actor.h"
#include "SpawnerManager.generated.h"

UCLASS()
class PONKRUNNER_API ASpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnerManager();

protected:
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void SetSpawnersEnabled(bool enabled);

	UFUNCTION()
	void AddSpawner(ASpawnerBase* spawner);
	
	UFUNCTION()
	void RemoveSpawner(ASpawnerBase* spawner);
	void SetSpawnersDifficulty(float difficultyValue);

	UPROPERTY(EditAnywhere)
	TArray<ASpawnerBase*> Spawners;
};
