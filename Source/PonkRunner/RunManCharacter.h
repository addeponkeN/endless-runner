// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "ObstacleCollider.h"
#include "RunnerHUD.h"
#include "RunnerPlayerController.h"
#include "WeaponController.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "RunManCharacter.generated.h"

UCLASS()
class PONKRUNNER_API ARunManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ResetRunMan();

	void RunManJump(float v);

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 50.f;

	UFUNCTION()
	void OnColliderOverlapBegin(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHealthChanged();

	UPROPERTY()
	URunnerHUD* HUD;

	// UObstacleCollider* ObstacleReceiver;
	UPROPERTY(EditAnywhere)
	UHealthComponent* Health;

	UPROPERTY()
	ARunnerPlayerController* RunPlayerController;

	// UPROPERTY()
	// UWeaponController* WeaponController;
	
private:
	UPROPERTY()
	float _direction;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RunnerMesh;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* RunnerCamera;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;

	UPROPERTY(EditAnywhere)
	TSubclassOf<URunnerHUD> HUDClass;


	void MoveHorizontal(float direction);
	void MoveHorizontalRelativeToActor(float direction);
};
