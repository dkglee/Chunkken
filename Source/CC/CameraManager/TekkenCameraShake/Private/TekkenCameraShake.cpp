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
	
	// 1. 멤버 변수로 TSoftClassPtr을 선언 (Header)
	TSoftClassPtr<UCameraShakeBase> TekkenCSBase;

	// 2. 생성자 또는 적절한 위치에서 경로를 설정 (소프트 레퍼런스이므로 즉시 로드되지 않음)
	TekkenCSBase = TSoftClassPtr<UCameraShakeBase>(FSoftObjectPath(TEXT("/Game/Camera/CS_MyCameraShake.CS_MyCameraShake_C")));

	// 3. 실제 사용 시 로드
	if (TekkenCSBase.IsValid()) // 이미 로드되었는지 확인
	{
		CameraShakeSettings.Add(ECameraSequence::ECS_None, TekkenCSBase.Get());
	}
	else // 로드되지 않았다면 로드 요청
	{
		UClass* LoadedClass = TekkenCSBase.LoadSynchronous(); // 동기 로드 (비추천, 가능하면 비동기 사용)
		if (LoadedClass)
		{
			CameraShakeSettings.Add(ECameraSequence::ECS_None, LoadedClass);
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
