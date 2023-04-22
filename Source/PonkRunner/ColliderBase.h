// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ColliderBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverlapEvent, AActor*, OtherActor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PONKRUNNER_API UColliderBase : public USceneComponent
{
	GENERATED_BODY()

public:
	UColliderBase();

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UShapeComponent> ColliderTemplate;

	UPROPERTY(EditAnywhere)
	UShapeComponent* Collider;

	UPROPERTY(BlueprintAssignable)
	FOnOverlapEvent OnOverlapBeginEvent;

	UPROPERTY(BlueprintAssignable)
	FOnOverlapEvent OnOverlapEndEvent;

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(
		UPrimitiveComponent* overlappedComp,
		AActor* otherActor,
		UPrimitiveComponent* otherComp,
		int32 otherBodyIndex, bool fromSweep, const FHitResult& result);
	UFUNCTION()
	virtual void OnOverlapEnd(
		UPrimitiveComponent* overlappedComp,
		AActor* otherActor,
		UPrimitiveComponent* otherComp,
		int32 otherBodyIndex);
};
