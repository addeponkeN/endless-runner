// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformManager.h"

#include "PonkRunnerGameModeBase.h"

// Sets default values
APlatformManager::APlatformManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlatformManager::BeginPlay()
{
	Super::BeginPlay();

	auto baseGameMode = GetWorld()->GetAuthGameMode();
	auto gameMode = Cast<APonkRunnerGameModeBase>(baseGameMode);
	auto gameMode2 = dynamic_cast<APonkRunnerGameModeBase*>(baseGameMode);
	WorldAnchor = gameMode->WorldAnchor;
	WorldAnchor = gameMode2->WorldAnchor;
}

// Called every frame
void APlatformManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

