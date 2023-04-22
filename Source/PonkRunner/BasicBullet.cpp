// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicBullet.h"

#include "ActorPool.h"

void ABasicBullet::Kill()
{
	Super::Kill();
	ActorPool<ABasicBullet>::Return(this);
}
