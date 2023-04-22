// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreEntry.h"

// HighScoreItem::HighScoreItem()
// {
// }

// HighScoreItem::~HighScoreItem()
// {
// }

// bool FHighScoreEntry::operator<(const FHighScoreEntry& other) const
// {
// }
FString FHighScoreEntry::GetFormattedString() const
{
	return FString::Printf(TEXT("%s: %i"), *Name, Score);
}

FString FHighScoreEntry::GetFormattedStringRanked(const int32 i) const
{
	return FString::Printf(TEXT("%i. %s: %i"), i, *Name, Score);
}
