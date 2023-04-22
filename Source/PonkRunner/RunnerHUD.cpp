// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerHUD.h"


void URunnerHUD::SetHealth(const int32& health)
{
	FText healthDisplayText = FText::AsNumber(health);
	LbHealth->SetText(healthDisplayText);
}

void URunnerHUD::SetScore(const int32& score)
{
	FText scoreDisplayText = FText::AsNumber(score);
	LbScore->SetText(scoreDisplayText);
}
