// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Components/SceneComponent.h"
#include "DustTrailParticleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PONKRUNNER_API UDustTrailParticleComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UDustTrailParticleComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* NiagaraTemplate;
	
};
