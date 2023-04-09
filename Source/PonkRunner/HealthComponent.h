// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthValueChanged);

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
	FHealthValueChanged OnValueChangedEvent;

	UPROPERTY(EditAnywhere)
	float Value;

	UPROPERTY(EditInstanceOnly)
	float MaxValue;

	void Damage(float amount);
	void Heal(float amount);

	void Kill();

	void SetValue(float newValue);
};
