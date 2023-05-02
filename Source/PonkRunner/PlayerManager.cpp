// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerManager.h"

#include "PonkRunner.h"
#include "PonkRunnerGameModeBase.h"
#include "Kismet/GameplayStatics.h"

APlayerManager::APlayerManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerManager::BeginPlay()
{
	Super::BeginPlay();

	Start();
}

void APlayerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (int i = 0; i < Runners.Num(); ++i)
	{
		Runners[i]->UpdateRunner(DeltaTime);
	}
}

ARunManCharacter* APlayerManager::GetPlayerOne()
{
	return Runners[0];
}

void APlayerManager::Start()
{
	APonkRunnerGameModeBase* gameMode = APonkRunnerGameModeBase::GetMode(GetWorld());
	Runners.Push(gameMode->RunMan);

	auto player2Controller = UGameplayStatics::CreatePlayer(GetWorld(), 1, true);

	if (player2Controller)
	{
		LOG("spawned p2");
		auto player2Pawn = player2Controller->GetPawn();
		ARunManCharacter* player2 = Cast<ARunManCharacter>(player2Pawn);
		if (player2)
		{
			LOG("added p2");
			Runners.Push(player2);
			gameMode->RunMan->OtherRunner = player2;
		}
	}


	for (int i = 0; i < Runners.Num(); ++i)
	{
		Runners[i]->FinalizeCharacter();
	}

	for (int i = 0; i < Runners.Num(); ++i)
	{
		auto runner = Runners[i];
		auto local = runner->RunPlayerController->GetLocalPlayer();
		LOG(FString::Printf(TEXT("P%i - Controllerid:%i"),
			i, local->GetControllerId()));
	}
}

void APlayerManager::SetRunnerInputEnabled(bool enabled) const
{
	for (int i = 0; i < Runners.Num(); ++i)
	{
		ARunManCharacter* runner = Runners[i];
		ARunnerPlayerController* controller = runner->RunPlayerController;

		if (!controller)
		{
			// LOG(FString::Printf(TEXT("Player %i controller was null"), i));
			continue;
		}

		if (enabled)
		{
			runner->EnableInput(controller);
		}
		else
		{
			runner->DisableInput(controller);
		}
		// if (i < 1)
		// {
			controller->SetCursorEnabled(!enabled);
		// }

		// LOG(FString::Printf(TEXT("Set input enable for %i to %i"), i, enabled));
	}
}

void APlayerManager::ResetRunners()
{
	for (int i = 0; i < Runners.Num(); ++i)
	{
		Runners[i]->ResetRunMan();
	}
}
