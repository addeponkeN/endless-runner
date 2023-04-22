// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleCollider.h"

#include "ObstacleBase.h"
#include "PonkRunner.h"

UObstacleCollider::UObstacleCollider()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Box = Cast<UBoxComponent>(GetOwner()->GetComponentByClass(UBoxComponent::StaticClass()));
	// if (!Box)
	// {
		// Box = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
		// Box->SetupAttachment(this);
	// }

	// Box->OnComponentBeginOverlap.AddDynamic(this, &UObstacleCollider::OnOverlapBegin);
}

void UObstacleCollider::OnOverlapBegin(
	UPrimitiveComponent* overlappedComp,
	AActor* otherActor,
	UPrimitiveComponent* otherComp,
	int32 otherBodyIndex,
	bool fromSweep,
	const FHitResult& result)
{
	if (AObstacleBase* obs = Cast<AObstacleBase>(otherActor))
	{
		Super::OnOverlapBegin(overlappedComp, otherActor, otherComp, otherBodyIndex, fromSweep, result);
		// obs->OnHitReceiver(this);
		LOG(otherComp->GetName());
	}
}
