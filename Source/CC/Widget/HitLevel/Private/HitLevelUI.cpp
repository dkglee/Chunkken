// Fill out your copyright notice in the Description page of Project Settings.


#include "HitLevelUI.h"

#include "Components/TextBlock.h"

void UHitLevelUI::SetHitLevel(const FString& Level)
{
	HitLevel->SetText(FText::FromString(Level));
	PlayAnimation(TextDestructed, 0, 1, EUMGSequencePlayMode::Forward, 1.0f);
}
