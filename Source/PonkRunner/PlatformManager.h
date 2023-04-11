// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformBase.h"
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

	UPROPERTY(EditAnywhere)
	APlatformBase* Template;

	TArray<APlatformBase*> Platforms;

	UPROPERTY(EditAnywhere)
	int PlatformCount = 12;

	UPROPERTY(EditAnywhere)
	AActor* WorldAnchor;

private:

	void PlacePlatform(APlatformBase* platform);
	
	APlatformBase* _lastPlatform;

	int32 _lastPlatformIndex;
	float _platformFrontPosition;
};
