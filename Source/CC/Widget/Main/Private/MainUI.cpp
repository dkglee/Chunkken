// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

#include "GaugeUI.h"
#include "HitComboUI.h"

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

void UMainUI::UpdateHitInfo(int32 HitCombo, int32 Damage, bool bIsLeftPlayer, bool bActive)
{
	if (bIsLeftPlayer)
	{
		WBP_HitComboL->SetRenderOpacity(1.0f);
		WBP_DamageL->SetRenderOpacity(1.0f);
		WBP_HitComboL->UpdateHitInfo(HitCombo);
		WBP_DamageL->UpdateHitInfo(Damage);
	}
	else
	{
		WBP_HitComboR->SetRenderOpacity(1.0f);
		WBP_DamageR->SetRenderOpacity(1.0f);
		WBP_HitComboR->UpdateHitInfo(HitCombo);
		WBP_DamageR->UpdateHitInfo(Damage);
	}
	UWidgetAnimation* AnimToPlay = GetDamageAnimation(bIsLeftPlayer, bActive);
	if (AnimToPlay)
	{
		PlayAnimation(AnimToPlay);
	}
}

UWidgetAnimation* UMainUI::GetDamageAnimation(bool bIsLeftPlayer, bool bActive) const
{
	// 왼쪽이고 && Active : DamageOccuredDuringLeft
	// 오른쪽이고 && Active : DamageOccuredDuringRight
	// 왼쪽이고 && !Active : DamageOccuredLeft
	// 오른쪽이고 && !Active : DamageOccuredRight
	if (bIsLeftPlayer)
	{
		return bActive ? DamageOccuredDuringLeft : DamageOccuredLeft;
	}
	else
	{
		return bActive ? DamageOccuredDuringRight : DamageOccuredRight;
	}
}

void UMainUI::HideHitInfo(bool bIsLeftPlayer)
{
	if (bIsLeftPlayer)
	{
		PlayAnimation(HideLeft);
	}
	else
	{
		PlayAnimation(HideRight);
	}
}
