// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHud.h"

void UGameHud::SetScore(const int32& score)
{
	const FText scoreDisplayText = FText::AsNumber(score);
	LbScore->SetText(scoreDisplayText);
}
