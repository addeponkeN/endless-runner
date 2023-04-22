// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverPanel.h"

#include "PonkRunnerGameModeBase.h"

void UGameOverPanel::NativeConstruct()
{
	Super::NativeConstruct();

	BtMenu->OnClicked.AddDynamic(this, &UGameOverPanel::GoToMainMenu);
}

void UGameOverPanel::SetHighScore(const int32& score) const
{
	const FText scoreDisplayText = FText::AsNumber(score);
	LbScore->SetText(scoreDisplayText);
}

void UGameOverPanel::GoToMainMenu()
{
	const APonkRunnerGameModeBase* mode = Cast<APonkRunnerGameModeBase>(GetWorld()->GetAuthGameMode());

	const FString name = TbName->GetText().ToString();
	if (!name.IsEmpty())
	{
		const int32 score = mode->ScoreManager->CurrentScore;
		mode->HighScoreManager->AddEntry(name, score);
	}

	mode->SetStateMenu();
}
