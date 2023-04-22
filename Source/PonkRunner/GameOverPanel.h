// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "GameOverPanel.generated.h"

/**
 * 
 */
UCLASS()
class PONKRUNNER_API UGameOverPanel : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void SetHighScore(const int32& score) const;

	UFUNCTION()
	void GoToMainMenu();
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LbGameOver;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LbScoreMessage;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LbScore;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* BtMenu;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UEditableTextBox* TbName;
	
};
