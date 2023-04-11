// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformBase.h"

// Sets default values
APlatformBase::APlatformBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	// RootComponent = Mesh;
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	
}

// Called when the game starts or when spawned
void APlatformBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlatformBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float APlatformBase::GetSizeX()
{
	return Box->Bounds.BoxExtent.X;
}
