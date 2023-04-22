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
}

void UHealthComponent::SetValue(const float& newValue)
{
	//	add this check to avoid unnecessary broadcasting if the value is the same
	if (Value != newValue)
	{
		Value = FMath::Clamp(newValue, 0.f, MaxValue);
		OnValueChangedEvent.Broadcast();
	}
}

void UHealthComponent::Damage(const float& amount)
{
	SetValue(Value - amount);
}

void UHealthComponent::Heal(const float& amount)
{
	SetValue(Value + amount);
}

void UHealthComponent::Kill()
{
	Value = 0;
}

void UHealthComponent::ResetHealth()
{
	Value = MaxValue;
}
