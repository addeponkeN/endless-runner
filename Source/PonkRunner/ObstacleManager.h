// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObstacle.h"
#include "ActorPool.h"
#include "GameFramework/Actor.h"
#include "ObstacleManager.generated.h"

UCLASS()
class PONKRUNNER_API AObstacleManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ABaseObstacle* SpawnObstacle(FVector const* position);

	void DespawnObstacle(ABaseObstacle* obstacle);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ObstacleTemplate;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TestTemplate;
	
	UPROPERTY(EditAnywhere)
	AActor* WorldAnchor;

private:
	TArray<ABaseObstacle*> _obstacles;
};
