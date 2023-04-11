// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleManager.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class PONKRUNNER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()

public:	
	AObstacleSpawner();

protected:
	virtual void BeginPlay() override;

private:
	float GetIntervalTime() const;


public:
	
	UFUNCTION(BlueprintCallable)
	void SetSpawningEnabled(bool enabled);

	UFUNCTION(BlueprintCallable)
	void SpawnActor();

	void UpdateSpawnPositionOrigin();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool SpawningEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnIntervalRandomOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Area;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorToSpawn;


private:
	FTimerManager* _timerManager;
	FTimerHandle _timerHandle;

	UPROPERTY(EditAnywhere)
	AObstacleManager* _obManager;

	void ScheduleSpawn();
	void SpawnActorScheduled();

	FVector GetRandomAreaPosition() const;
};
