// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletCollider.h"

#include "BulletBase.h"
#include "PonkRunner.h"

UBulletCollider::UBulletCollider()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UBulletCollider::BeginPlay()
{
	Super::BeginPlay();
	// Collider = Cast<UShapeComponent>(GetOwner()->GetComponentByClass(UShapeComponent::StaticClass()));
	// if(Collider)
	// {
		// LOG("set collider");
	// }
	// else
	// {
		// LOG("no collider found");
	// }
}

void UBulletCollider::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor,
	UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool fromSweep, const FHitResult& result)
{
	Super::OnOverlapBegin(overlappedComp, otherActor, otherComp, otherBodyIndex, fromSweep, result);
	if(ABulletBase* bullet = Cast<ABulletBase>(otherActor))
	{
		bullet->Kill();
	}
}

