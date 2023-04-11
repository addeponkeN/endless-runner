// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Components/SceneComponent.h"
#include "WeaponSlot.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PONKRUNNER_API UWeaponSlot : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponSlot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AWeaponBase* wep);

	UFUNCTION()
	void OnControllerFire();

	UFUNCTION()
	void OnControllerFireRelease();


	UPROPERTY(EditAnywhere, Category="Weapon")
	TSubclassOf<AWeaponBase> StartWeapon;

	UPROPERTY(EditAnywhere)
	AWeaponBase* Weapon;
	
};
