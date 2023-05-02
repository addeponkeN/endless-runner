// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RunManCharacter.h"

#include "GameFramework/Actor.h"
#include "PlayerManager.generated.h"

UCLASS()
class PONKRUNNER_API APlayerManager : public AActor
{
	GENERATED_BODY()

public:
	APlayerManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	ARunManCharacter* GetPlayerOne();

	void Start();
	void SetRunnerInputEnabled(bool enabled) const;
	void ResetRunners();

	UPROPERTY(VisibleAnywhere)
	TArray<ARunManCharacter*> Runners;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARunManCharacter> RunnerTemplate;
	
};
