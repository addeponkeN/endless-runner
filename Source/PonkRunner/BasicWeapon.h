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

	virtual void FireStart() override;

};
