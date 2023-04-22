// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
// class PONKRUNNER_API HighScoreItem
// {
// public:
// 	HighScoreItem();
// 	~HighScoreItem();
// };

// USTRUCT(BlueprintType)
struct FHighScoreEntry
{
	FString Name;
	int32 Score;

	FString GetFormattedString() const;
	FString GetFormattedStringRanked(int i) const;

	FHighScoreEntry(): Name(TEXT("nub")), Score(0){}
	FHighScoreEntry(const FString& name, const int32 score): Name(name), Score(score){}
	FORCEINLINE bool operator<(const FHighScoreEntry& other) const
	{
		return (Score > other.Score);
	}
};
