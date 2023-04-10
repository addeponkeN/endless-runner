// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RunnerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PONKRUNNER_API URunnerHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHealth(const int32 health);

	void SetScore(const int32 score);

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LbHealth;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LbScore;

};
