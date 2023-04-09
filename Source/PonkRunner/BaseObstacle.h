// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Poolable.h"
#include "GameFramework/Actor.h"
#include "BaseObstacle.generated.h"

UCLASS()
class PONKRUNNER_API ABaseObstacle : public APoolable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 250.f;

};
