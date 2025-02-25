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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* LeftDamaged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* RightDamaged;
	
	void UpdateHP(int32 HP, int32 MaxHP, bool bIsLeftPlayer);
};
