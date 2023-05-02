// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RunManCharacter.h"
#include "ScoreManager.h"
#include "Components/ActorComponent.h"

#include "RunnerScoreController.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PONKRUNNER_API URunnerScoreController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URunnerScoreController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void StartTickScore();
	void StopTickScore();
	void AddTickScore();

	UFUNCTION()
	void SetEnabled(bool isEnabled);

	UPROPERTY()
	bool IsEnabled;

	UPROPERTY(BlueprintReadWrite)
	float ScoreGainInterval;

	UPROPERTY(BlueprintReadWrite)
	float ScoreGainedPerTick;

	ARunManCharacter* Runner;
	UScoreManager* ScoreManager;

private:
	FTimerHandle _timerHandle;
};
