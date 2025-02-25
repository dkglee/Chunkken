// Fill out your copyright notice in the Description page of Project Settings.


#include "HitComboUI.h"

#include "Components/TextBlock.h"

void UHitComboUI::UpdateHitInfo(int32 InText)
{
	Hits->SetText(FText::FromString(FString::FromInt(InText)));
	PlayAnimation(DamageOccured);
}
