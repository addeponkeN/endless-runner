// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreChangedEvent);

UCLASS()
class PONKRUNNER_API UScoreManager : public UObject
{
	GENERATED_BODY()
	
public:
	UScoreManager();

	void StartTickScore();
	void StopTickScore();

	UFUNCTION(BlueprintCallable)
	void AddScore(float score);
	
	UPROPERTY(BlueprintReadOnly)
	float CurrentScore;

	UPROPERTY(BlueprintReadWrite)
	float ScoreGainInterval;
	
	UPROPERTY(BlueprintReadWrite)
	float ScoreGainedPerTick;

	UPROPERTY(BlueprintCallable)
	FOnScoreChangedEvent OnScoreChangedEvent;


private:
	void AddTickScore();
	
	FTimerHandle _timerHandle;
};
