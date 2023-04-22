// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HighScoreTextBlock.generated.h"

/**
 * 
 */
UCLASS()
class PONKRUNNER_API UHighScoreTextBlock : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetScore(const FText& entryText);

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* LbEntry;
};

