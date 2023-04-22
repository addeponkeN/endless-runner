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
	APoolable();

protected:
	bool IsActive = true;

public:
	virtual void Spawned();
	virtual void Returned();

	void OnCreated(const FName& folderPath);

private:
	void SetActive(bool isActive);
};
