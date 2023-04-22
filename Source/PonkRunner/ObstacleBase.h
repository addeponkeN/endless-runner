// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleCollider.h"
#include "Poolable.h"
#include "GameFramework/Actor.h"
#include "ObstacleBase.generated.h"

UCLASS()
class PONKRUNNER_API AObstacleBase : public APoolable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Reset() override;
	void UpdateObstacle(float dt);
	bool IsOutOfBounds(FVector const* runnerPosition) const;

	UFUNCTION()
	void OnColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
									const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void Kill();
	
	UFUNCTION(BlueprintCallable)
	virtual void OnHitByBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 250.f;

	UPROPERTY(BlueprintReadOnly)
	bool IsAlive = true;

	UPROPERTY(EditAnywhere)
	bool KillWhenHit = true;

	UPROPERTY(VisibleAnywhere)
	bool KilledByPlayer;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;
	
	// UPROPERTY(EditAnywhere)
	// UBulletCollider* BulletCollider;
};
