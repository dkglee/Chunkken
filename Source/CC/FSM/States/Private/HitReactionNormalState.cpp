// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionNormalState.h"

#include "AnimUtils.h"
#include "BaseCharacter.h"
#include "CameraManager.h"
#include "ECameraSequence.h"
#include "EditorAnimUtils.h"
#include "FastLogger.h"
#include "TekkenAnimIntance.h"
#include "TekkenCameraShake.h"

FString UHitReactionNormalState::StateName = TEXT("HIT_REACTION_NORMAL");

FString UHitReactionNormalState::GetStateName()
{
	return StateName;
}

void UHitReactionNormalState::PlayAnimation(const FString& String, int32 INT32)
{
	if (String.IsEmpty() || INT32 < 0)
	{
		FFastLogger::LogConsole(TEXT("String is Empty or INT32 is less than 0"));
		return;
	}

	// SocketID = Odd : Left | Even : Right // 애니메이션 재생
	FString Anim = TEXT("");
	if (String.Equals(TEXT("HIGH")))
	{
		if (INT32 % 2 == 0)
		{
			Anim = TEXT("HeadHitRight");
		}
		else
		{
			Anim = TEXT("HeadHitLeft");
		}
	}
	else if (String.Equals(TEXT("MIDDLE")))
	{
		if (INT32 % 2 == 0)
		{
			Anim = TEXT("BodyHitRight");
		}
		else
		{
			Anim = TEXT("BodyHitLeft");
		}
	}
	else if (String.Equals(TEXT("LOW")))
	{
		// Low에 대한 처리를 여기에 작성
	}
	else
	{
		// 그 외의 처리를 여기에 작성
	}

	if (Anim.IsEmpty())
	{
		FFastLogger::LogConsole(TEXT("Anim is Empty"));
		return;
	}

	UAnimMontage* Montage = TekkenAnimInstance->GetMontageFromName(Anim);
	if (!Montage)
	{
		FFastLogger::LogConsole(TEXT("Montage is nullptr"));
		return;
	}

	float PlayRate = FAnimUtils::CalculateAnimPlayRate(25, Montage->GetSectionLength(0));
	PlayRate = FMath::Clamp(PlayRate, 0.0f, 2.3f);
	TekkenAnimInstance->PlayMontageModule(Anim, PlayRate);
}

void UHitReactionNormalState::Exit()
{
	Super::Exit();
}

void UHitReactionNormalState::Enter()
{
	Super::Enter();

	HitAnimData = Me->CharacterState.HitAnimInfo;
	StunFrame = Me->CharacterState.HitStun;
	Me->CharacterState.HitAnimInfo = std::pair<FString, int32>(TEXT(""), -1);

	// Hit Level과 SocketType을 이용해서 애니메이션을 찾는다.
	FString HitLevel = HitAnimData.first;
	int32 SocketID = HitAnimData.second;

	PlayAnimation(HitLevel, SocketID);

	FVector LaunchDirection = {0.0f, 300.0f, 0.0f};
	if (Me->IsLeftPlayer())
	{
		LaunchDirection *= -1;
	}
	Me->LaunchCharacter(LaunchDirection, true, true);

	// Camera Shake
	CameraShakeManager->PlayerCameraShake(ECameraSequence::ECS_None, 1.0f);
}

void UHitReactionNormalState::Update()
{
	Super::Update();

}
