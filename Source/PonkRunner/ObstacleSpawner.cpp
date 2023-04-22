// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"

#include "ObstacleManager.h"
#include "ObstacleBase.h"
#include "Kismet/GameplayStatics.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	ActorPool<AObstacleBase>::Init(GetWorld(), ObstacleTemplate);
	_obManager = Cast<AObstacleManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AObstacleManager::StaticClass()));
}

void AObstacleSpawner::SpawnActor()
{
	Super::SpawnActor();

	//	update position of the spawner
	constexpr float offsetFromAnchor = 1500.f;
	const FVector anchor = _obManager->WorldAnchor->GetActorLocation();
	const FVector position = FVector(anchor.X + offsetFromAnchor, 0.f, 10.f);
	SetActorLocation(position);
	
	const FVector SpawnPosition = GetRandomAreaPosition();
	_obManager->SpawnObstacle<AObstacleBase>(&SpawnPosition);
}

FVector AObstacleSpawner::GetRandomAreaPosition() const
{
	FBoxSphereBounds bounds = Area->CalcBounds(GetActorTransform());
	FVector pos = bounds.Origin;
	pos.X += bounds.BoxExtent.X * (FMath::FRand() * 2.f - 1.f);
	pos.Y += bounds.BoxExtent.Y * (FMath::FRand() * 2.f - 1.f);
	pos.Z += bounds.BoxExtent.Z * (FMath::FRand() * 2.f - 1.f);
	return pos;
}
