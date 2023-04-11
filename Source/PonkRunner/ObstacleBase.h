// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleReceiver.h"
#include "Poolable.h"
#include "GameFramework/Actor.h"
#include "ObstacleBase.generated.h"

UCLASS()
class PONKRUNNER_API AObstacleBase : public APoolable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Reset() override;
	void UpdateObstacle(float dt);
	bool IsOutOfBounds(FVector const* runnerPosition);

	void OnHitReceiver(UObstacleReceiver* receiver);

	UFUNCTION(BlueprintCallable)
	void Kill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 250.f;

	UPROPERTY(BlueprintReadOnly)
	bool IsAlive = true;
};
