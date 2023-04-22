// Fill out your copyright notice in the Description page of Project Settings.


#include "DustTrailParticleComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

UDustTrailParticleComponent::UDustTrailParticleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UDustTrailParticleComponent::BeginPlay()
{
	Super::BeginPlay();
	NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraTemplate,
	                                                                  FVector::ZeroVector, FRotator::ZeroRotator);

	NiagaraComponent->AttachToComponent(GetOwner()->GetRootComponent(),
	                                    FAttachmentTransformRules::KeepRelativeTransform, TEXT("NiagaraCOmponenta"));
}


void UDustTrailParticleComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	NiagaraComponent->SetWorldLocation(GetComponentLocation());
}
