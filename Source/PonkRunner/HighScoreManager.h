// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FHighScoreEntry;

/**
 * 
 */
class PONKRUNNER_API HighScoreManager
{
public:
	HighScoreManager();
	~HighScoreManager();

	void AddEntry(const FString& name, const int32 score);

	void LoadHighScores();
	void SaveHighScores();
	TArray<FHighScoreEntry*> GetHighScores() { return Entries; }

private:
	void SortEntries();

	FString GetFullPath() const;

	TArray<FHighScoreEntry*> Entries;

	const FString FileName = "highscore.txt";
};
