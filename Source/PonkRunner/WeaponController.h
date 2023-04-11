// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFiredEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFireReleaseEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PONKRUNNER_API UWeaponController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintCallable)
	FOnWeaponFiredEvent OnFireEvent;

	UPROPERTY(BlueprintCallable)
	FOnWeaponFireReleaseEvent OnFireReleaseEvent;

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void FireRelease();
	
};
