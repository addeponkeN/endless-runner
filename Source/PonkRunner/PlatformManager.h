// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlatform.h"
#include "GameFramework/Actor.h"
#include "PlatformManager.generated.h"

UCLASS()
class PONKRUNNER_API APlatformManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatformManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PlatformTemplate;
	
	TArray<ABasePlatform*> Platforms;

	UPROPERTY(EditAnywhere)
	int PlatformsToSpawnAhead = 10;

	UPROPERTY(EditAnywhere)
	AActor* WorldAnchor;
};
