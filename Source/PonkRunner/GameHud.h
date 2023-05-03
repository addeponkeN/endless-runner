// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameHud.generated.h"

/**
 * 
 */
UCLASS()
class PONKRUNNER_API UGameHud : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetScore(const int32& score);

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LbScore;
};
