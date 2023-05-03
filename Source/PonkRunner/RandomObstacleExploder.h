// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleManager.h"
#include "Components/ActorComponent.h"
#include "RandomObstacleExploder.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PONKRUNNER_API URandomObstacleExploder : public UActorComponent
{
	GENERATED_BODY()

public:
	URandomObstacleExploder();

	UPROPERTY(EditAnywhere)
	float ExplodeChance = 0.2f;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void RollAndExplodeRandomObstacle(AObstacleBase* obstacle);

	UPROPERTY()
	AObstacleManager* ObstacleManager;
};
