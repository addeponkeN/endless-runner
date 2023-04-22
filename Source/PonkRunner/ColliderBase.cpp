// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderBase.h"

UColliderBase::UColliderBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UColliderBase::OnOverlapBegin(
	UPrimitiveComponent* overlappedComp,
	AActor* otherActor,
	UPrimitiveComponent* otherComp,
	int32 otherBodyIndex,
	bool fromSweep,
	const FHitResult& result)
{
	OnOverlapBeginEvent.Broadcast(otherActor);
}

void UColliderBase::OnOverlapEnd(
	UPrimitiveComponent* overlappedComp,
	AActor* otherActor,
	UPrimitiveComponent* otherComp,
	int32 otherBodyIndex)
{
	OnOverlapEndEvent.Broadcast(otherActor);
}
