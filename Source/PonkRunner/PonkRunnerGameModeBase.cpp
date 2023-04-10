// Copyright Epic Games, Inc. All Rights Reserved.


#include "PonkRunnerGameModeBase.h"

#include "PonkRunner.h"
#include "ToolBuilderUtil.h"
#include "GameFramework/DefaultPawn.h"

void APonkRunnerGameModeBase::InitGameState()
{
	Super::InitGameState();
	LOG("created score manager");
	ScoreManager = NewObject<UScoreManager>(this);

	bool isDefaultPawn = DefaultPawnClass == ADefaultPawn::StaticClass();

	if (isDefaultPawn || !DefaultPawnClass)
	{
		DefaultPawnClass = CustomRunnerCharacterClass;
	}
}

void APonkRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	auto controller = GetWorld()->GetFirstPlayerController();
	WorldAnchor = controller->GetCharacter();
}


void APonkRunnerGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
