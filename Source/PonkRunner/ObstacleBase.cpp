// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleBase.h"

// Sets default values
AObstacleBase::AObstacleBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AObstacleBase::BeginPlay()
{
	Super::BeginPlay();
}

void AObstacleBase::Reset()
{
	Super::Reset();
	IsAlive = true;
}

void AObstacleBase::UpdateObstacle(float dt)
{
	FVector pos = GetActorLocation();
	pos.X -= Speed * dt;
	SetActorLocation(pos);
}

bool AObstacleBase::IsOutOfBounds(FVector const* runnerPosition)
{
	return GetActorLocation().X < runnerPosition->X - 100.f;
}

void AObstacleBase::OnHitReceiver(UObstacleReceiver* receiver)
{
	Kill();
}

void AObstacleBase::Kill()
{
	IsAlive = false;
}
