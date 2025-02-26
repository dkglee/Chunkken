// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReadyFightUI.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UReadyFightUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void PlayReadyFightAnim();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* ReadyAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* FightAnim;
};
