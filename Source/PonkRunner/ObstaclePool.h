// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObstacle.h"
#include "GameFramework/Actor.h"
#include "ObstaclePool.generated.h"

UCLASS()
class PONKRUNNER_API AObstaclePool : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstaclePool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame

	ABaseObstacle* Create() const;
	ABaseObstacle* Get();
	void Return(ABaseObstacle* obstacle);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ObstacleTemplate;

private:
	TArray<ABaseObstacle*> _pool;
};
