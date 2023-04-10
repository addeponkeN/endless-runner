// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManager.h"

#include "PonkRunner.h"

UScoreManager::UScoreManager()
{
	CurrentScore = 0.f;
	ScoreGainInterval = 0.25f;
	ScoreGainedPerTick = 1.f;
}

void UScoreManager::StartTickScore()
{
	GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &UScoreManager::AddTickScore, ScoreGainInterval, true);
	LOG("started tick score");
}

void UScoreManager::StopTickScore()
{
	GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void UScoreManager::AddScore(float score)
{
	CurrentScore += score;
	OnScoreChangedEvent.Broadcast();
}

void UScoreManager::AddTickScore()
{
	AddScore(ScoreGainedPerTick);
}
