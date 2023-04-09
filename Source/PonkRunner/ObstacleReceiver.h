// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "ObstacleReceiver.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObstacleReceiverOverlapEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PONKRUNNER_API UObstacleReceiver : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObstacleReceiver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintAssignable)
	FOnObstacleReceiverOverlapEvent OnTriggerEvent;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

private:
	UFUNCTION()
	void OnObstacleOverlapBegin(
		UPrimitiveComponent* overlappedComp,
		AActor* otherActor,
		UPrimitiveComponent* otherComp,
		int32 otherBodyIndex, bool fromSweep, const FHitResult& result);
	UFUNCTION()
	void OnObstacleOverlapEnd(
		UPrimitiveComponent* overlappedComp,
		AActor* otherActor,
		UPrimitiveComponent* otherComp,
		int32 otherBodyIndex);
};
