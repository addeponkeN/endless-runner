// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletBase.h"
#include "BasicBullet.generated.h"

/**
 * 
 */
UCLASS()
class PONKRUNNER_API ABasicBullet : public ABulletBase
{
	GENERATED_BODY()

	virtual void Kill() override;
};
