// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGui.h"

#include "HighScoreEntry.h"
#include "HighScoreTextBlock.h"
#include "PonkRunner.h"
#include "PonkRunnerGameModeBase.h"

void UMainMenuGui::NativeConstruct()
{
	Super::NativeConstruct();

	BtStart->OnClicked.AddDynamic(this, &UMainMenuGui::StartGame);
	BtQuit->OnClicked.AddDynamic(this, &UMainMenuGui::QuitGame);

	LOG("setup button events");
	
}

void UMainMenuGui::StartGame()
{
	const APonkRunnerGameModeBase* gameMode = Cast<APonkRunnerGameModeBase>(GetWorld()->GetAuthGameMode());
	gameMode->SetStatePlay();
}

void UMainMenuGui::QuitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}

void UMainMenuGui::UpdateScores()
{
	const APonkRunnerGameModeBase* mode = APonkRunnerGameModeBase::GetMode(GetWorld());
	TArray<FHighScoreEntry*> arrScores = mode->HighScoreManager->GetHighScores();

	VbScores->ClearChildren();
	
	for (int i = 0; i < arrScores.Num(); ++i)
	{
		FHighScoreEntry* entry = arrScores[i];
		
		FString entryString = entry->GetFormattedStringRanked(i);
		const FText entryText = FText::FromString(entryString);
		
		UHighScoreTextBlock* textBlock = CreateWidget<UHighScoreTextBlock>(this, ScoreEntryTextBlockTemplate);
		
		textBlock->LbEntry->SetText(entryText);
		VbScores->AddChild(textBlock);
	}
}

void UMainMenuGui::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	if (InVisibility == ESlateVisibility::Visible)
	{
		UpdateScores();
	}
}
