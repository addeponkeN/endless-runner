// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColliderBase.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "ObstacleCollider.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PONKRUNNER_API UObstacleCollider : public UColliderBase
{
	GENERATED_BODY()

public:
	UObstacleCollider();

	// UPROPERTY(EditAnywhere)
	// UBoxComponent* Box;

	virtual void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor,
	                                    UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool fromSweep,
	                                    const FHitResult& result) override;
};
