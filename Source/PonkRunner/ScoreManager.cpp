// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManager.h"

UScoreManager::UScoreManager()
{
	CurrentScore = 0.f;
}

void UScoreManager::AddScore(float score)
{
	CurrentScore += score;
	OnScoreChangedEvent.Broadcast();
}

void UScoreManager::ResetScore()
{
	CurrentScore = 0.f;
	OnScoreChangedEvent.Broadcast();
}
