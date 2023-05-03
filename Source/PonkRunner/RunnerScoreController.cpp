// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerScoreController.h"

#include "PonkRunner.h"
#include "PonkRunnerGameModeBase.h"

URunnerScoreController::URunnerScoreController()
{
	PrimaryComponentTick.bCanEverTick = false;
	Runner = Cast<ARunManCharacter>(GetOwner());
	ScoreGainInterval = 0.2f;
	ScoreGainedPerTick = 1.f;
}

void URunnerScoreController::BeginPlay()
{
	Super::BeginPlay();

	APonkRunnerGameModeBase* gameMode = Cast<APonkRunnerGameModeBase>(GetWorld()->GetAuthGameMode());

	ScoreManager = gameMode->ScoreManager;
}

void URunnerScoreController::StartTickScore()
{
	GetWorld()->GetTimerManager()
	          .SetTimer(_timerHandle, this, &URunnerScoreController::AddTickScore, ScoreGainInterval, true);
}

void URunnerScoreController::StopTickScore()
{
	GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void URunnerScoreController::AddTickScore()
{
	ScoreManager->AddScore(ScoreGainedPerTick);
}

void URunnerScoreController::SetEnabled(bool isEnabled)
{
	IsEnabled = isEnabled;
	if (IsEnabled)
	{
		StartTickScore();
	}
	else
	{
		StopTickScore();
	}
}
