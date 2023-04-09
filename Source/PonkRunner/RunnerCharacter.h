// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "RunnerCharacter.generated.h"

UCLASS()
class PONKRUNNER_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunnerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 50.f;
	
private:

	UPROPERTY()
	float _direction;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RunnerMesh;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* RunnerCamera;
	
	void MoveHorizontal(float direction);
	void MoveHorizontalRelativeToActor(float direction);
};
