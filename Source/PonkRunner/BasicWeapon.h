// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "BasicWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PONKRUNNER_API ABasicWeapon : public AWeaponBase
{
	GENERATED_BODY()

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void FireStart() override;
	virtual void SpawnBullet() override;
};
