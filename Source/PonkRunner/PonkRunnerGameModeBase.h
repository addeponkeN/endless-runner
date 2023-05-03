// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameOverPanel.h"
#include "MainMenuGui.h"
#include "RunManCharacter.h"
#include "ScoreManager.h"
#include "SpawnerManager.h"
#include "DifficultyManager.h"
#include "GameHud.h"
#include "HighScoreManager.h"
#include "PlatformManager.h"
#include "PlayerManager.h"
#include "GameFramework/GameModeBase.h"
#include "PonkRunnerGameModeBase.generated.h"

class URunnerScoreController;
/**
 *	THE SPAGHETT
 */
UCLASS()
class PONKRUNNER_API APonkRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APonkRunnerGameModeBase();
	
	static APonkRunnerGameModeBase* GetMode(const UWorld* world);
	virtual void InitGameState() override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void InitDifficultyManager();


public:
	UFUNCTION()
	void ScoreValueChanged();
	
	UFUNCTION()
	void RunnerHealthChanged();

	UFUNCTION()
	void DifficultyValueChanged();

	UFUNCTION()
	void ObstacleKilled();

	void SetStatePlay();
	void SetStateMenu() const;
	void SetStateGameOver() const;

	// void SetRunnerInputEnabled(bool enabled) const;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<ARunManCharacter> CustomRunnerCharacterClass = ARunManCharacter::StaticClass();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	UScoreManager* ScoreManager;

	UPROPERTY(EditAnywhere)
	URunnerScoreController* ScoreController;

	UPROPERTY(EditAnywhere)
	ASpawnerManager* SpawnerManager;

	UPROPERTY(EditAnywhere)
	APlatformManager* PlatformManager;

	UPROPERTY(EditAnywhere)
	APlayerManager* PlayerManager;

	UPROPERTY(EditAnywhere)
	AObstacleManager* ObstacleManager;

	//	aka the player
	UPROPERTY(EditAnywhere)
	ARunManCharacter* RunMan;

	UPROPERTY(EditAnywhere)
	ADifficultyManager* DifficultyManager;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainMenuGui> MenuGuiTemplate;

	UPROPERTY(EditAnywhere)
	UMainMenuGui* MenuGui;

	// UPROPERTY(EditAnywhere)
	// URunnerHUD* RunnerHud;

	// UPROPERTY(EditAnywhere)
	// TSubclassOf<URunnerHUD> RunnerHudTemplate;

	UPROPERTY(EditAnywhere)
	UGameHud* GameHud;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameHud> GameHudTemplate;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameOverPanel> GameOverPanelTemplate;

	UPROPERTY(EditAnywhere)
	UGameOverPanel* GameOverPanel;

	HighScoreManager* HighScoreManager;
	

private:
	bool _inited;
	void SetPointers();
};
