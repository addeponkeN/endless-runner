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

	_platformFrontPosition = -50.f;

	for (int i = 0; i < PlatformCount; ++i)
	{
		APlatformBase* platform = GetWorld()->SpawnActor<APlatformBase>(PlatformTemplate);
		platform->SetFolderPath(TEXT("Platforms"));
		PlacePlatform(platform);
		Platforms.Add(platform);
	}

	_lastPlatformIndex = 0;
	_lastPlatform = Platforms[_lastPlatformIndex];
}

// Called every frame
void APlatformManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// FVector anchor = WorldAnchor->GetActorLocation();
	// float endOfLine = anchor.X - 200.f;

	// ABasePlatform* p = _lastPlatform;
	// if (p->GetActorLocation().X < endOfLine)
	// {
	// PlacePlatform(p);
	// _lastPlatformIndex++;
	// if (_lastPlatformIndex >= Platforms.Num())
	// _lastPlatformIndex = 0;
	// _lastPlatform = Platforms[_lastPlatformIndex];
	// }
}

void APlatformManager::PlacePlatform(APlatformBase* platform)
{
	FVector position = FVector(_platformFrontPosition, 0.f, 0.f);
	platform->SetActorLocation(position);
	_platformFrontPosition += platform->GetSizeX() * 2.f;
}
