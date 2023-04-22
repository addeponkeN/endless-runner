// Fill out your copyright notice in the Description page of Project Settings.


#include "WallObstacle.h"

AWallObstacle::AWallObstacle()
{
	PrimaryActorTick.bCanEverTick = false;
	KillWhenHit = false;
}

void AWallObstacle::BeginPlay()
{
	Super::BeginPlay();
}

void AWallObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
