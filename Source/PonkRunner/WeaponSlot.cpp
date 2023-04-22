// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSlot.h"

#include "WeaponController.h"

// Sets default values for this component's properties
UWeaponSlot::UWeaponSlot()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UWeaponSlot::BeginPlay()
{
	Super::BeginPlay();

	if(StartWeapon && !Weapon)
	{
		Weapon = GetWorld()->SpawnActor<AWeaponBase>(StartWeapon);
		Weapon->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
	
	AActor* owner = GetOwner();
	UWeaponController* controller = Cast<UWeaponController>(
		owner->GetComponentByClass(UWeaponController::StaticClass()));
	
	if (controller)
	{
		controller->OnFireEvent.AddDynamic(this, &UWeaponSlot::OnControllerFire);
		controller->OnFireReleaseEvent.AddDynamic(this, &UWeaponSlot::OnControllerFireRelease);
	}

}

void UWeaponSlot::EquipWeapon(AWeaponBase* wep)
{
	Weapon = wep;
}

void UWeaponSlot::OnControllerFire()
{
	if (!Weapon)
		return;

	Weapon->FireStart();
}

void UWeaponSlot::OnControllerFireRelease()
{
	if (!Weapon)
		return;
	
	Weapon->FireEnd();
}
