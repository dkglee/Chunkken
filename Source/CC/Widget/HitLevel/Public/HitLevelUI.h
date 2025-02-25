// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitLevelUI.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UHitLevelUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHitLevel(const FString& Level);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* HitLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* TextDestructed;
};
