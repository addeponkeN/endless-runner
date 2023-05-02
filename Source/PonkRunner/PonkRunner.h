// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//	## ####### ##
//	## LOGGING ##
//	## ####### ##

#define LOG(x) PonkLog(FColor::White, x)
#define LOGI(x) PonkLog(FColor::Cyan, x);
#define LOGE(x) PonkLog(FColor::Red, x);
#define LOGW(x) PonkLog(FColor::Yellow, x);

static void PonkLog(FColor color, const FString& msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, color, msg);
}

//	## ####### ##
//	## ####### ##