// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RunnerCharacter.h"
#include "ScoreManager.h"
#include "GameFramework/GameModeBase.h"
#include "PonkRunnerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PONKRUNNER_API APonkRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGameState() override;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<ARunnerCharacter> CustomRunnerCharacterClass = ARunnerCharacter::StaticClass();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	UScoreManager* ScoreManager;

	//	also known as the Runner (ARunnerCharacter)
	UPROPERTY()
	AActor* WorldAnchor;
};
