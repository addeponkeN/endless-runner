// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "DifficultyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDifficultyValueChangedEvent);

UCLASS()
class PONKRUNNER_API ADifficultyManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADifficultyManager();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void Start();
	UFUNCTION(BlueprintCallable)
	void Stop();
	
	void ScheduleTimer();

	UFUNCTION()
	void IncrementTimer();

	/**
 * 0 = easy\n
 * 1 = hard\n
 * based on time passed, {time / MaxTime}
 */
	UPROPERTY(VisibleAnywhere)
	float DifficultyValue;

	/**
	 * @brief Time it takes to reach the hardest difficulty
	 */
	UPROPERTY(EditAnywhere)
	float MaxTime = 20.f;

	UPROPERTY(VisibleAnywhere)
	bool IsRunning = false;

	UPROPERTY()
	FOnDifficultyValueChangedEvent OnDifficultyValueChangedEvent;

private:
	UFUNCTION()
	void SetTimer(float v);

	UPROPERTY()
	float _timer;

	UPROPERTY(EditAnywhere)
	float _tickInterval = 1.f;

	FTimerHandle _timerHandle;
};
