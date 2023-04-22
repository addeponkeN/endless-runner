// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformManager.h"

#include "PonkRunner.h"
#include "PonkRunnerGameModeBase.h"

APlatformManager::APlatformManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlatformManager::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* baseGameMode = GetWorld()->GetAuthGameMode();
	auto gameMode = Cast<APonkRunnerGameModeBase>(baseGameMode);
	WorldAnchor = gameMode->RunMan;
	auto gameMode2 = dynamic_cast<APonkRunnerGameModeBase*>(baseGameMode);
	WorldAnchor = gameMode2->RunMan;


	//	spawn initial platforms
	_platformFrontPosition = -100.f;
	for (int i = 0; i < PlatformCount; ++i)
	{
		APlatformBase* platform = GetWorld()->SpawnActor<APlatformBase>(PlatformTemplate);
		// #ifdef !UE_BUILD_SHIPPING
		// platform->SetFolderPath(TEXT("Platforms"));
		// #endif
		PlacePlatform(platform);
		Platforms.Add(platform);
	}

	SetTexturePanningSpeed(400.f);
}

void APlatformManager::SetTexturePanningSpeed(float speed)
{
	FLinearColor pannerSpeed;
	pannerSpeed.R = speed * .01f;
	pannerSpeed.G = 0.f;
	pannerSpeed.B = 0.f;
	pannerSpeed.A = 1.f;
	for (APlatformBase* platform : Platforms)
	{
		TArray<UStaticMeshComponent*> meshes;
		platform->GetComponents<UStaticMeshComponent>(meshes);
		for (UStaticMeshComponent* mesh : meshes)
		{
			UMaterialInterface* material = mesh->GetMaterial(0);
			UMaterialInstanceDynamic* dynamicMaterial = Cast<UMaterialInstanceDynamic>(material);

			if (!dynamicMaterial)
			{
				dynamicMaterial = UMaterialInstanceDynamic::Create(material, mesh);
				dynamicMaterial->SetVectorParameterValue(TEXT("PannerSpeed"), pannerSpeed);
				mesh->SetMaterial(0, dynamicMaterial);
			}
			else
			{
				dynamicMaterial->SetVectorParameterValue(TEXT("PannerSpeed"), pannerSpeed);
			}
		}
	}
}

void APlatformManager::SetDifficulty(float difficulty)
{
	const float speed = FMath::Lerp(50.f, 600.f, difficulty);
	LOG(FString::FromInt(speed));
	SetTexturePanningSpeed(speed);
}

void APlatformManager::PlacePlatform(APlatformBase* platform)
{
	FVector position = FVector(_platformFrontPosition, 0.f, 0.f);
	platform->SetActorLocation(position);
	_platformFrontPosition += platform->GetSizeX() * 2.f;
}
