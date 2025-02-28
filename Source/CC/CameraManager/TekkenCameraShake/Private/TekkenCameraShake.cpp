// Fill out your copyright notice in the Description page of Project Settings.

#include "TekkenCameraShake.h"
#include "Camera/CameraShakeBase.h"
#include "ECameraSequence.h"
#include "FastLogger.h"

UTekkenCameraShakeManager::UTekkenCameraShakeManager()
{
	bWantsInitializeComponent = true;
}

void UTekkenCameraShakeManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
}

void UTekkenCameraShakeManager::InitializeComponent()
{
	Super::InitializeComponent();

	// 카메라 셰이크 데이터 매핑
	TMap<ECameraSequence, FSoftObjectPath> CameraShakePaths = {
		{ ECameraSequence::ECS_None, FSoftObjectPath(TEXT("/Game/Camera/CS_MyCameraShake.CS_MyCameraShake_C")) },
		{ ECameraSequence::ECS_Airbone, FSoftObjectPath(TEXT("/Game/Camera/BP_AirboneShake.BP_AirboneShake_C")) },
		{ ECameraSequence::ECS_KO, FSoftObjectPath(TEXT("/Game/Camera/BP_KOShake.BP_KOShake_C")) },
		{ ECameraSequence::ECS_StrongHit, FSoftObjectPath(TEXT("/Game/Camera/BP_StrongShake.BP_StrongShake_C")) },
		{ ECameraSequence::ECS_WeakHit, FSoftObjectPath(TEXT("/Game/Camera/BP_WeakShake.BP_WeakShake_C")) }
	};

	// 모든 카메라 셰이크 클래스 로드
	for (const auto& Entry : CameraShakePaths)
	{
		LoadCameraShakeClass(Entry.Key, Entry.Value);
	}
}

/**
 * 특정 카메라 셰이크 클래스를 로드하는 함수
 */
void UTekkenCameraShakeManager::LoadCameraShakeClass(ECameraSequence SequenceType, const FSoftObjectPath& ObjectPath)
{
	TSoftClassPtr<UCameraShakeBase> CameraShakeClass(ObjectPath);

	if (CameraShakeClass.IsValid())
	{
		CameraShakeSettings.Add(SequenceType, CameraShakeClass.Get());
	}
	else
	{
		UClass* LoadedClass = CameraShakeClass.LoadSynchronous(); // 동기 로드
		if (LoadedClass)
		{
			CameraShakeSettings.Add(SequenceType, LoadedClass);
		}
	}
}


void UTekkenCameraShakeManager::PlayerCameraShake(ECameraSequence CameraSequence, float Intensity)
{
	if (CameraShakeSettings.Contains(CameraSequence) == false)
	{
		FFastLogger::LogConsole(TEXT("CameraShakeSettings is not valid"));
		return;
	}
	FFastLogger::LogConsole(TEXT("CameraShakeSettings is valid"));
	PlayerController->PlayerCameraManager->StartCameraShake(CameraShakeSettings[CameraSequence], Intensity);
}
