// Copyright Epic Games, Inc. All Rights Reserved.


#include "PonkRunnerGameModeBase.h"

#include "GameFramework/DefaultPawn.h"

void APonkRunnerGameModeBase::InitGameState()
{
	Super::InitGameState();

	bool isDefaultPawn = DefaultPawnClass == ADefaultPawn::StaticClass();

	if (isDefaultPawn || !DefaultPawnClass)
	{
		DefaultPawnClass = CustomRunnerCharacterClass;
	}
}
