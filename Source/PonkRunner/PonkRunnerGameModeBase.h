// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RunnerCharacter.h"
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

private:

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<ARunnerCharacter> CustomRunnerCharacterClass = ARunnerCharacter::StaticClass();
	
};
