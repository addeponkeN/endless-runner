// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poolable.generated.h"

UCLASS()
class PONKRUNNER_API APoolable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APoolable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool IsActive = true;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetActive(bool isActive);
};
