// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicWeapon.h"

#include "ActorPoolv2.h"
#include "BasicBullet.h"

void ABasicWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (ActorPoolv2<ABasicBullet>::IsInitialized)
		ActorPoolv2<ABasicBullet>::Clear();
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

	if (!ActorPoolv2<ABasicBullet>::IsInitialized)
	{
		ActorPoolv2<ABasicBullet>::Init(GetWorld());
	}

	ABasicBullet* bullet = ActorPoolv2<ABasicBullet>::Spawn(BulletTemplate);
	bullet->Start(&direction);
}


