// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"

#include "ActorPool.h"
#include "ObstacleBase.h"
#include "PonkRunner.h"

ABulletBase::ABulletBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Bulletu"));
	Collider->SetupAttachment(Mesh);
}

void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABulletBase::OnColliderOverlapBegin);
}

void ABulletBase::Spawned()
{
	Super::Spawned();
	_position = GetActorLocation();
	GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &ABulletBase::Kill, LifeTime);
}

void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_position += Direction * (Speed * DeltaTime);
	SetActorLocation(_position);
}

void ABulletBase::OnColliderOverlapBegin(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (AObstacleBase* obs = Cast<AObstacleBase>(OtherActor))
	{
		Kill();
		obs->OnHitByBullet();
	}
}

void ABulletBase::Start(FVector const* direction)
{
	_started = true;
	Direction = *direction;
}

void ABulletBase::Kill()
{
	GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}
