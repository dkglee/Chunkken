// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

#include "GaugeUI.h"

void UMainUI::UpdateHP(int32 HP, int32 MaxHP, bool bIsLeftPlayer)
{
	if (bIsLeftPlayer)
	{
		WBP_Gauge_L->UpdateHP(HP, MaxHP);
		PlayAnimation(LeftDamaged, 0, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}
	else
	{
		WBP_Gauge_R->UpdateHP(HP, MaxHP);
		PlayAnimation(RightDamaged, 0, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}
}
