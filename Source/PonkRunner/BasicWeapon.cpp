// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicWeapon.h"

#include "ActorPool.h"
#include "BasicBullet.h"

void ABasicWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (ActorPool<ABasicBullet>::IsInitialized)
		ActorPool<ABasicBullet>::Clear();
}

void ABasicWeapon::FireStart()
{
	Super::FireStart();
}

void ABasicWeapon::SpawnBullet()
{
	Super::SpawnBullet();
	const FVector location = BulletSpawnLocation->GetComponentLocation();
	const FVector direction = BulletSpawnLocation->GetForwardVector();

	if (!ActorPool<ABasicBullet>::IsInitialized)
	{
		ActorPool<ABasicBullet>::Init(GetWorld(), BulletTemplate);
	}

	ABasicBullet* bullet = ActorPool<ABasicBullet>::Spawn(&location);
	bullet->Start(&direction);
}


