// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LogoUI.generated.h"
class UUserWidget;


UCLASS()
class CC_API ULogoUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget),Transient)
	UUserWidget* LogoAnimation;

protected:
	virtual void NativeConstruct() override;
	
};
