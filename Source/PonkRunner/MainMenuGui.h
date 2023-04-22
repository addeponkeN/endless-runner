// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HighScoreTextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/RichTextBlock.h"
#include "Components/VerticalBox.h"
#include "MainMenuGui.generated.h"

/**
 * 
 */
UCLASS()
class PONKRUNNER_API UMainMenuGui : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	UFUNCTION()
	void StartGame();

	void QuitGame();

	UFUNCTION()
	void UpdateScores();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHighScoreTextBlock> ScoreEntryTextBlockTemplate;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* BtStart;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* BtQuit;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UVerticalBox* VbScores;
	
};
