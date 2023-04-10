// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerScoreController.h"

#include "PonkRunnerGameModeBase.h"

// Sets default values for this component's properties
URunnerScoreController::URunnerScoreController()
{
	PrimaryComponentTick.bCanEverTick = false;
	Runner = Cast<ARunnerCharacter>(GetOwner());
}


// Called when the game starts
void URunnerScoreController::BeginPlay()
{
	Super::BeginPlay();
	
	APonkRunnerGameModeBase* gameMode = Cast<APonkRunnerGameModeBase>(GetWorld()->GetAuthGameMode());
	
	ScoreManager = gameMode->ScoreManager;
	ScoreManager->OnScoreChangedEvent.AddDynamic(this, &URunnerScoreController::OnScoreChanged);
	ScoreManager->StartTickScore();
}

void URunnerScoreController::OnScoreChanged()
{
	Runner->HUD->SetScore(ScoreManager->CurrentScore);
}
