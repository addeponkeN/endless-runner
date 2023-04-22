// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColliderBase.h"
#include "Components/SceneComponent.h"
#include "BulletCollider.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PONKRUNNER_API UBulletCollider : public UColliderBase
{
	GENERATED_BODY()

public:
	UBulletCollider();

protected:
	virtual void BeginPlay() override;

public:

	virtual void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	                            int32 otherBodyIndex, bool fromSweep, const FHitResult& result) override;
};
