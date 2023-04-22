// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Poolable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BulletBase.generated.h"

UCLASS()
class PONKRUNNER_API ABulletBase : public APoolable
{
	GENERATED_BODY()

public:
	ABulletBase();

	virtual void Spawned() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

	void Start(FVector const* direction);

	virtual void Kill();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere)
	FVector Direction;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float LifeTime = 4.f;

private:
	bool _started;
	FVector _position;
	FTimerHandle _timerHandle;
};
