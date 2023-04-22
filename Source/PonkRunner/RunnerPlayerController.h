// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RunnerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PONKRUNNER_API ARunnerPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

public:
	void SetCursorEnabled(bool enable);
};
