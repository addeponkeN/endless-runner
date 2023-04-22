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
	
	UFUNCTION(BlueprintCallable)
	void AddScore(float score);

	UFUNCTION(BlueprintCallable)
	void ResetScore();

	UPROPERTY(BlueprintReadOnly)
	float CurrentScore;

	UPROPERTY(BlueprintCallable)
	FOnScoreChangedEvent OnScoreChangedEvent;
};
