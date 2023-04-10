// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthValueChangedEvent);

// could add an OnDeathEvent, but might become too bloated

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PONKRUNNER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FHealthValueChangedEvent OnValueChangedEvent;

	UPROPERTY(EditAnywhere)
	float Value;

	UPROPERTY(EditInstanceOnly)
	float MaxValue = 1.f;

	UFUNCTION(BlueprintCallable)
	void SetValue(const float& newValue);

	UFUNCTION(BlueprintCallable)
	void Damage(const float& amount);

	UFUNCTION(BlueprintCallable)
	void Heal(const float& amount);

	UFUNCTION(BlueprintCallable)
	void Kill();
};
