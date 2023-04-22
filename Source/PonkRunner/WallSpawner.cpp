// Fill out your copyright notice in the Description page of Project Settings.


#include "WallSpawner.h"

#include "ObstacleManager.h"
#include "WallObstacle.h"
#include "Kismet/GameplayStatics.h"

AWallSpawner::AWallSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnIntervalMin = 6.f;
	SpawnIntervalMin = 1.5f;
	SpawnIntervalRandomOffset = 0.1f;

	_obManager = Cast<AObstacleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AObstacleManager::StaticClass()));
}

void AWallSpawner::BeginPlay()
{
	Super::BeginPlay();
	ActorPool<AWallObstacle>::Init(GetWorld(), WallObstacleTemplate);
}

void AWallSpawner::SpawnActor()
{
	Super::SpawnActor();

	constexpr float offsetFromAnchor = 1500.f;
	const FVector anchor = _obManager->WorldAnchor->GetActorLocation();
	const FVector position = FVector(anchor.X + offsetFromAnchor, 0.f, 10.f);
	SetActorLocation(position);

	const FBoxSphereBounds bounds = Area->CalcBounds(GetActorTransform());

	const FVector center = bounds.Origin;

	FVector left = FVector(center.X, center.Y - bounds.BoxExtent.Y, center.Z);
	FVector right = FVector(center.X, center.Y + bounds.BoxExtent.Y, center.Z);

	const float roomWidth = right.Y - left.Y;

	constexpr float holeMinSize = 60.f;
	constexpr float holeMaxSize = 500.f;

	const float holeSize = FMath::Lerp(holeMaxSize, holeMinSize, Difficulty);

	float sizePool = roomWidth - holeSize;

	const auto wallLeft = _obManager->SpawnObstacle<AWallObstacle>(&left);

	const float leftScale = FMath::FRandRange(sizePool * .1f, sizePool * .9f);
	sizePool -= leftScale;

	const FVector currentScale = wallLeft->GetActorScale3D();
	FVector scale = FVector(currentScale.X, leftScale / 50.f, currentScale.Z);

	wallLeft->SetActorScale3D(scale);

	scale.Y = sizePool / 50.f;
	const auto wallRight = _obManager->SpawnObstacle<AWallObstacle>(&right);
	wallRight->SetActorScale3D(scale);
}

void AWallSpawner::SetSpawningEnabled(bool enabled)
{
	Super::SetSpawningEnabled(enabled);
}
