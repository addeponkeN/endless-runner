// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerHUD.h"


void URunnerHUD::SetHealth(const int32 health)
{
	FString healthText = FString::FromInt(health);
	FText healthDisplayText = FText::FromString(healthText);
	LbHealth->SetText(healthDisplayText);
}

void URunnerHUD::SetScore(const int32 score)
{
	FString scoreText = FString::FromInt(score);
	FText scoreDisplayText = FText::FromString(scoreText);
	LbScore->SetText(scoreDisplayText);
}
