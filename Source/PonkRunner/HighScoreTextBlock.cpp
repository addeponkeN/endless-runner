// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreTextBlock.h"

#include "PonkRunner.h"


void UHighScoreTextBlock::SetScore(const FText& entryText)
{
	LbEntry->SetText(entryText);
}

void UHighScoreTextBlock::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	auto item = Cast<UHighScoreTextBlock>(ListItemObject);
	if(item)
	{
		item->LbEntry->SetText(FText::FromString(TEXT("yesas")));
		auto lbTExt = item->LbEntry->GetText();
		LOG("set text onlistitemobjectset");
		LOG(lbTExt.ToString());
	}
}