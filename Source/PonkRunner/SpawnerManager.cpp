// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerManager.h"

ASpawnerManager::ASpawnerManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpawnerManager::BeginPlay()
{
	Super::BeginPlay();
	SetSpawnersEnabled(false);
}

void ASpawnerManager::SetSpawnersEnabled(bool enabled)
{
	for (ASpawnerBase* spawner : Spawners)
	{
		spawner->SetSpawningEnabled(enabled);
	}
}

void ASpawnerManager::AddSpawner(ASpawnerBase* spawner)
{
	Spawners.Push(spawner);
}

void ASpawnerManager::RemoveSpawner(ASpawnerBase* spawner)
{
	Spawners.Remove(spawner);
}

void ASpawnerManager::SetSpawnersDifficulty(float difficultyValue)
{
	for (int i = 0; i < Spawners.Num(); ++i)
	{
		Spawners[i]->Difficulty = difficultyValue;
	}
}
