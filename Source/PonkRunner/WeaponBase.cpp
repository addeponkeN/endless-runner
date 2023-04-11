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
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_timer > 0.f)
	{
		_timer -= DeltaTime;
	}

	if (IsFireDown)
	{
		if (_timer <= 0.f)
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
	LOG("Weapon Fire Tick");
	_timer = FireRate;
}

bool AWeaponBase::CanFire()
{
	return _timer <= 0.f;
}
