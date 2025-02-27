// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KOUI.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UKOUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void PlayKOAnim();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* KOAnim;
};
