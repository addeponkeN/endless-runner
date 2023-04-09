// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleReceiver.h"

#include "BaseObstacle.h"
#include "PonkRunner.h"

// Sets default values for this component's properties
UObstacleReceiver::UObstacleReceiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("ReceiverBox"));
	Box->SetupAttachment(this);

	Box->OnComponentBeginOverlap.AddDynamic(this, &UObstacleReceiver::OnObstacleOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &UObstacleReceiver::OnObstacleOverlapEnd);
}


// Called when the game starts
void UObstacleReceiver::BeginPlay()
{
	Super::BeginPlay();
}

void UObstacleReceiver::OnObstacleOverlapBegin(UPrimitiveComponent* overlappedComp,
                                               AActor* otherActor,
                                               UPrimitiveComponent* otherComp,
                                               int32 otherBodyIndex, bool fromSweep, const FHitResult& result)
{
	if (ABaseObstacle* obs = dynamic_cast<ABaseObstacle*>(otherActor))
	{
		OnTriggerEvent.Broadcast();
		LOG("Overlapped Obstacle!");
	}
}

void UObstacleReceiver::OnObstacleOverlapEnd(UPrimitiveComponent* overlappedComp, AActor* otherActor,
                                             UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	LOG("OVERLAP END");
}
