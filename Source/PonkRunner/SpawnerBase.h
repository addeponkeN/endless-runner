// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerBase.generated.h"

class AObstacleManager;
class UBoxComponent;

UCLASS()
class PONKRUNNER_API ASpawnerBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float GetIntervalTime() const;

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetSpawningEnabled(bool enabled);

	UFUNCTION(BlueprintCallable)
	virtual void SpawnActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool SpawningEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnIntervalMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnIntervalMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnIntervalRandomOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Area;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorToSpawn;

protected:
	FTimerManager* _timerManager;
	FTimerHandle _timerHandle;

	void ScheduleSpawn();
	void SpawnActorScheduled();
};
