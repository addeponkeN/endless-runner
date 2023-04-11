// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponController.h"

// Sets default values for this component's properties
UWeaponController::UWeaponController()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponController::BeginPlay()
{
	Super::BeginPlay();
	AActor* owner = GetOwner();
	UInputComponent* input = Cast<UInputComponent>(owner->GetComponentByClass(UInputComponent::StaticClass()));
	if (input)
	{
		input->BindAction(TEXT("Fire"), IE_Pressed, this, &UWeaponController::Fire);
		input->BindAction(TEXT("Fire"), IE_Released, this, &UWeaponController::FireRelease);
	}
}

void UWeaponController::Fire()
{
	OnFireEvent.Broadcast();
}

void UWeaponController::FireRelease()
{
	OnFireReleaseEvent.Broadcast();
}
