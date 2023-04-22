// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

#include "BulletBase.h"
#include "WallObstacle.h"

template class ActorPool<AObstacleBase>;
template class ActorPool<ABulletBase>;
template class ActorPool<AWallObstacle>;
