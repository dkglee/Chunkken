// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameManager.h"

#include "FastLogger.h"
#include "GameFramework/GameUserSettings.h"


UFrameManager::UFrameManager()
{
}


void UFrameManager::BeginPlay()
{
	Super::BeginPlay();

	// 60 FPS 고정
	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
	Settings->SetFrameRateLimit(60.0f);
	Settings->ApplyNonResolutionSettings();
}

void UFrameManager::UpdateFrame(float DeltaSeconds)
{
	FrameTime += DeltaSeconds;
	FrameIndex += 1;
}

uint64 UFrameManager::GetFrameIndex() const
{
	return FrameIndex;
}

