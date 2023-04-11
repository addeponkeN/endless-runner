// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class PONKRUNNER_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// UFUNCTION(BlueprintCallable)
	virtual void FireStart();

	// UFUNCTION(BlueprintCallable)
	virtual void FireEnd();

	virtual void FireTick();

	UFUNCTION(BlueprintCallable)
	bool CanFire();

	UPROPERTY(BlueprintReadOnly)
	bool IsFireDown;

	UPROPERTY(BlueprintReadWrite)
	float FireRate = 0.5f;

private:
	FTimerHandle _timerHandle;
	float _timer;
};
