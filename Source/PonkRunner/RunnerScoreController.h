// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunnerCharacter.h"
#include "ScoreManager.h"
#include "Components/ActorComponent.h"
#include "RunnerScoreController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	UFUNCTION()
	void OnScoreChanged();

	ARunnerCharacter* Runner;
	UScoreManager* ScoreManager;

};
