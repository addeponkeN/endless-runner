// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "PonkRunner.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	BulletSpawnLocation = Cast<UArrowComponent>(GetComponentByClass(UArrowComponent::StaticClass()));
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_fireRateTimer > 0.f)
	{
		_fireRateTimer -= DeltaTime;
	}

	if (IsFireDown)
	{
		if (_fireRateTimer <= 0.f)
		{
			FireTick();
		}
	}
}

void AWeaponBase::FireStart()
{
	// LOG("Weapon Fire Start");
	IsFireDown = true;
	if (CanFire())
		FireTick();
}

void AWeaponBase::FireEnd()
{
	IsFireDown = false;
	// LOG("Weapon Fire End");
}

void AWeaponBase::FireTick()
{
	// LOG("Weapon Fired");
	_fireRateTimer = FireRate;
	SpawnBullet();
}

void AWeaponBase::SpawnBullet()
{
}

bool AWeaponBase::CanFire()
{
	return _fireRateTimer <= 0.f;
}
