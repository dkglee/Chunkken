// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GaugeUI.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UGaugeUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* RedBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* BlackBar;

	void UpdateHP(int32 HP, int32 MaxHP);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	virtual void NativeDestruct() override;
	
	FTimerHandle TimerHandle;
	float UpdateDelay = 0.5f;
	void UpdateBlackHP(float Percent);
	float TargetBlackBarPercent = 0.0f;
	bool bShouldUpdateBlackBar = false;
};
