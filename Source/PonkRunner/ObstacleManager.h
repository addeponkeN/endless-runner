// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActorPool.h"
#include "ObstacleBase.h"

#include "GameFramework/Actor.h"
#include "ObstacleManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObstacleKilledEvent);

UCLASS()
class PONKRUNNER_API AObstacleManager : public AActor
{
	GENERATED_BODY()

public:
	AObstacleManager();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaTime) override;

	// template <typename T, std::enable_if_t<std::is_base_of_v<APoolable, T>, int>>
	template <typename T>
	T* SpawnObstacle(FVector const* position);

	UFUNCTION(BlueprintCallable)
	void DespawnObstacle(AObstacleBase* obstacle);
	
	UFUNCTION(BlueprintCallable)
	void ClearObstacles();
	
	UPROPERTY()
	FOnObstacleKilledEvent OnObstacleKilledEvent;

	UPROPERTY(EditAnywhere)
	AActor* WorldAnchor;

private:
	UPROPERTY()
	TArray<AObstacleBase*> _obstacles;
};


template <typename T>
T* AObstacleManager::SpawnObstacle(FVector const* position)
{
	T* obstacle = ActorPool<T>::Spawn(position);
	_obstacles.Add(obstacle);
	return obstacle;
}
