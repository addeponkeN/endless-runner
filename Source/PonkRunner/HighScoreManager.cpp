// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreManager.h"

#include "HighScoreEntry.h"

HighScoreManager::HighScoreManager()
{
}

HighScoreManager::~HighScoreManager()
{
}

void HighScoreManager::AddEntry(const FString& name, const int32 score)
{
	FHighScoreEntry* entry = new FHighScoreEntry(name, score);
	Entries.Add(entry);
	SortEntries();
}

void HighScoreManager::LoadHighScores()
{
	TArray<FString> input;
	const FString path = GetFullPath();
	FFileHelper::LoadFileToStringArray(input, *path);

	for (int i = 0; i < input.Num(); ++i)
	{
		FString data = input[i];
		FString name;
		FString score;
		data.Split(data, &name, &score);
		FHighScoreEntry* item = new FHighScoreEntry(data, FCString::Atoi(*score));
		Entries.Add(item);
	}
}

void HighScoreManager::SaveHighScores()
{
	AddEntry(TEXT("john"), 69);
	AddEntry(TEXT("sven"), 33);
	AddEntry(TEXT("cone"), 41);
	AddEntry(TEXT("kony"), 2012);
	
	TArray<FString> output;

	for (int i = 0; i < Entries.Num(); ++i)
	{
		const FHighScoreEntry* item = Entries[i];
		FString strScore = FString::FromInt(item->Score);
		FString data = FString::Printf(TEXT("%s: %s"), *item->Name, *strScore);
		output.Add(data);
	}

	const FString path = GetFullPath();
	FFileHelper::SaveStringArrayToFile(output, *path);
}

void HighScoreManager::SortEntries()
{
	Entries.Sort();
}

FString HighScoreManager::GetFullPath() const
{
	return FPaths::Combine(*FPaths::ProjectDir(), FileName);
}


