// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	MaxValue = Value;
	// ...
}

void UHealthComponent::Damage(float amount)
{
	SetValue(Value - amount);
}

void UHealthComponent::Heal(float amount)
{
	SetValue(Value + amount);
}

void UHealthComponent::Kill()
{
	Value = 0;
}

void UHealthComponent::SetValue(float newValue)
{
	Value = newValue;
	OnValueChangedEvent.Broadcast();
}
