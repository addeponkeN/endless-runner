// Fill out your copyright notice in the Description page of Project Settings.


#include "Poolable.h"

// Sets default values
APoolable::APoolable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoolable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APoolable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoolable::SetActive(bool isActive)
{
	IsActive = isActive;
	// SetHidden(!_isActive);
	SetActorHiddenInGame(!IsActive);
}



