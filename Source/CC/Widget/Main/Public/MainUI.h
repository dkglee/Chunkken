// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UGaugeUI* WBP_Gauge_L;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UGaugeUI* WBP_Gauge_R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UHitComboUI* WBP_HitComboL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UHitComboUI* WBP_HitComboR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UHitComboUI* WBP_DamageL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UHitComboUI* WBP_DamageR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* LeftDamaged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* RightDamaged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* DamageOccuredLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* DamageOccuredRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* DamageOccuredDuringLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* DamageOccuredDuringRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* HideLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* HideRight;
	
	void UpdateHP(int32 HP, int32 MaxHP, bool bIsLeftPlayer);
	void UpdateHitInfo(int32 HitCombo, int32 Damage, bool bIsLeftPlayer, bool bActive);
	UWidgetAnimation* GetDamageAnimation(bool bIsLeftPlayer, bool bActive) const;
	void HideHitInfo(bool bIsLeftPlayer);	
};
