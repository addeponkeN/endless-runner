// Copyright Epic Games, Inc. All Rights Reserved.


#include "PonkRunnerGameModeBase.h"

#include "DifficultyManager.h"
#include "ObstacleManager.h"
#include "PonkRunner.h"
#include "RunnerPlayerController.h"
#include "RunnerScoreController.h"
#include "GameFramework/DefaultPawn.h"
#include "Kismet/GameplayStatics.h"


APonkRunnerGameModeBase::APonkRunnerGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

APonkRunnerGameModeBase* APonkRunnerGameModeBase::GetMode(const UWorld* world)
{
	return Cast<APonkRunnerGameModeBase>(world->GetAuthGameMode());
}

void APonkRunnerGameModeBase::InitGameState()
{
	Super::InitGameState();

	HighScoreManager = new class HighScoreManager;
	HighScoreManager->SaveHighScores();

	ScoreManager = NewObject<UScoreManager>(this);

	const bool isDefaultPawn = DefaultPawnClass == ADefaultPawn::StaticClass();

	if (isDefaultPawn || !DefaultPawnClass)
	{
		DefaultPawnClass = CustomRunnerCharacterClass;
	}
}

void APonkRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ARunnerPlayerController* playerController = Cast<ARunnerPlayerController>(GetWorld()->GetFirstPlayerController());

	RunMan = Cast<ARunManCharacter>(playerController->GetCharacter());

	ScoreController = Cast<URunnerScoreController>(RunMan->GetComponentByClass(URunnerScoreController::StaticClass()));

	SpawnerManager = Cast<ASpawnerManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnerManager::StaticClass()));

	ObstacleManager = Cast<AObstacleManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AObstacleManager::StaticClass()));

	PlatformManager = Cast<APlatformManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), APlatformManager::StaticClass()));

	//	somehow GetActorOfClass returns null in BeginPlay() . .
	//	have to set it in Tick()
	// DifficultyManager = Cast<ADifficultyManager>(
	// UGameplayStatics::GetActorOfClass(GetWorld(), ADifficultyManager::StaticClass());

	InitDifficultyManager();

	MenuGui = CreateWidget<UMainMenuGui>(playerController, MenuGuiTemplate);
	MenuGui->AddToPlayerScreen();
	MenuGui->UpdateScores();

	GameOverPanel = CreateWidget<UGameOverPanel>(playerController, GameOverPanelTemplate);
	GameOverPanel->AddToPlayerScreen();
	GameOverPanel->SetVisibility(ESlateVisibility::Hidden);

	playerController->SetCursorEnabled(true);

	RunMan->Health->OnValueChangedEvent.AddDynamic(this, &APonkRunnerGameModeBase::RunnerHealthChanged);
	ObstacleManager->OnObstacleKilledEvent.AddDynamic(this, &APonkRunnerGameModeBase::ObstacleKilled);
}

void APonkRunnerGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!DifficultyManager)
	{
		LOG("difficultymanager was null");
		InitDifficultyManager();
	}
}

void APonkRunnerGameModeBase::InitDifficultyManager()
{
	auto difficultyManagerGetActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADifficultyManager::StaticClass());
	DifficultyManager = Cast<ADifficultyManager>(difficultyManagerGetActor);
	if (DifficultyManager)
	{
		DifficultyManager->OnDifficultyValueChangedEvent.AddDynamic(
			this, &APonkRunnerGameModeBase::DifficultyValueChanged);
		LOG("set difficultymanager");
	}
	else
	{
		LOG("FAILED set difficultymanager");
	}
}

void APonkRunnerGameModeBase::RunnerHealthChanged()
{
	if (RunMan->Health->Value <= 0)
	{
		SetStateGameOver();
	}
}

void APonkRunnerGameModeBase::DifficultyValueChanged()
{
	SpawnerManager->SetSpawnersDifficulty(DifficultyManager->DifficultyValue);
	// PlatformManager->SetDifficulty(DifficultyManager->DifficultyValue);
}

void APonkRunnerGameModeBase::ObstacleKilled()
{
	int obstacleWorth = 10;
	// todo : set obstacle worth
	//obstacleWorth = obstacleWorth->GetWorth();
	ScoreManager->AddScore(obstacleWorth);
}


/////////////////////////////////
// scuffed game state handling //
/////////////////////////////////

// todo : implement statemachine & game states (main menu, playing, game over)

// PLAY //
void APonkRunnerGameModeBase::SetStatePlay() const
{
	//	set player hud visible
	RunMan->HUD->SetVisibility(ESlateVisibility::Visible);

	SetRunnerInputEnabled(true);

	//	start the scorecontroller 
	ScoreController->StartTickScore();

	//	start all spawners
	SpawnerManager->SetSpawnersEnabled(true);

	//	hide menu gui
	MenuGui->SetVisibility(ESlateVisibility::Hidden);

	DifficultyManager->Start();
}


// MENU //
void APonkRunnerGameModeBase::SetStateMenu() const
{
	//	hide gameover panel
	GameOverPanel->SetVisibility(ESlateVisibility::Hidden);

	//	show menu
	MenuGui->SetVisibility(ESlateVisibility::Visible);

	//	disable player input
	SetRunnerInputEnabled(false);

	//	show cursor
	RunMan->RunController->SetCursorEnabled(true);

	ScoreManager->ResetScore();

	RunMan->RunController->SetPause(false);

	RunMan->ResetRunMan();

	//	remove any obstacles on the map
	ObstacleManager->ClearObstacles();
}


// GAME OVER //
void APonkRunnerGameModeBase::SetStateGameOver() const
{
	//	hide player hud
	RunMan->HUD->SetVisibility(ESlateVisibility::Hidden);

	//	show game over panel
	GameOverPanel->SetVisibility(ESlateVisibility::Visible);

	SetRunnerInputEnabled(false);

	GameOverPanel->SetHighScore(ScoreManager->CurrentScore);

	ScoreController->StopTickScore();

	SpawnerManager->SetSpawnersEnabled(false);

	RunMan->RunController->SetPause(true);

	DifficultyManager->Stop();

	auto weaponController = Cast<UWeaponController>(RunMan->GetComponentByClass(UWeaponController::StaticClass()));
	weaponController->FireRelease();
}


/////////////////////////////////
/////////////////////////////////


void APonkRunnerGameModeBase::SetRunnerInputEnabled(bool enabled) const
{
	ARunnerPlayerController* controller = RunMan->RunController;

	if (enabled)
	{
		RunMan->EnableInput(controller);
	}
	else
	{
		RunMan->DisableInput(controller);
	}

	//	hide cursor
	controller->SetCursorEnabled(!enabled);
}
