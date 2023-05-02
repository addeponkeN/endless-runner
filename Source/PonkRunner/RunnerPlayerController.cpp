// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerPlayerController.h"

#include "PonkRunner.h"

void ARunnerPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ARunnerPlayerController::SetCursorEnabled(bool enable)
{
	bShowMouseCursor = enable;
}


