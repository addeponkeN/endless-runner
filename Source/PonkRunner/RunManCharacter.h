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
	virtual void FinalizeCharacter();
	virtual void UpdateRunner(float dt);

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
	void P1_Fire();
	void P1_FireRelease();
	void P2_Fire();
	void P2_FireRelease();

	UPROPERTY()
	URunnerHUD* Hud;

	// UObstacleCollider* ObstacleReceiver;
	UPROPERTY(EditAnywhere)
	UHealthComponent* Health;

	UPROPERTY()
	ARunnerPlayerController* RunPlayerController;

	UPROPERTY(VisibleAnywhere)
	ARunManCharacter* OtherRunner;

	UPROPERTY()
	UWeaponController* WeaponController;

	UPROPERTY()
	float _direction;

private:
	UPROPERTY(VisibleAnywhere)
	int32 PlayerIndex;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RunnerMesh;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* RunnerCamera;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;

	UPROPERTY(EditAnywhere)
	TSubclassOf<URunnerHUD> HudTemplate;

	void P1_MoveHorizontal(float direction);
	void P2_MoveHorizontal(float direction);
	void MoveHorizontalRelativeToActor(float direction);
};
