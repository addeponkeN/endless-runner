// Fill out your copyright notice in the Description page of Project Settings.


#include "Poolable.h"

APoolable::APoolable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APoolable::Spawned()
{
	SetActive(true);
}

void APoolable::Returned()
{
	SetActive(false);
}

void APoolable::OnCreated(const FName& folderPath)
{
// #ifdef !UE_BUILD_SHIPPING
	// SetFolderPath(folderPath);
// #endif
}

void APoolable::SetActive(bool isActive)
{
	IsActive = isActive;
	SetActorTickEnabled(IsActive);
	SetActorEnableCollision(IsActive);
	SetActorHiddenInGame(!IsActive);
}
