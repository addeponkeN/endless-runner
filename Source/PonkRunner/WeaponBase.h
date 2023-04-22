// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletBase.h"
#include "Components/ArrowComponent.h"
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

	//	start firing (fire button is pressed)
	virtual void FireStart();

	//	stop firing (fire button is released)
	virtual void FireEnd();

	//	fire.
	virtual void FireTick();

	virtual void SpawnBullet();

	UFUNCTION(BlueprintCallable)
	bool CanFire();

	UPROPERTY(BlueprintReadOnly)
	bool IsFireDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate = 0.5f;

	UPROPERTY(EditAnywhere)
	UArrowComponent* BulletSpawnLocation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABulletBase> BulletTemplate;

private:
	float _fireRateTimer;
};
