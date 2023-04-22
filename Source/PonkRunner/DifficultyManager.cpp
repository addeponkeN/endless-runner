

#include "DifficultyManager.h"

#include "PonkRunner.h"

ADifficultyManager::ADifficultyManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADifficultyManager::BeginPlay()
{
	Super::BeginPlay();
}

void ADifficultyManager::Start()
{
	IsRunning = true;
	ScheduleTimer();
	LOG("diffi started");
}

void ADifficultyManager::Stop()
{
	IsRunning = false;
	SetTimer(0.f);
	GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void ADifficultyManager::IncrementTimer()
{
	SetTimer(_timer + _tickInterval);
	if (IsRunning)
	{
		ScheduleTimer();
	}
}

void ADifficultyManager::ScheduleTimer()
{
	GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &ADifficultyManager::IncrementTimer, _tickInterval);
}

void ADifficultyManager::SetTimer(float v)
{
	_timer = v;
	DifficultyValue = FMath::Clamp(_timer / MaxTime, 0.f, 1.f);
	OnDifficultyValueChangedEvent.Broadcast();
}
