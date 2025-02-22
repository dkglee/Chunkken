// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionNormalState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"
#include "TekkenAnimIntance.h"

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
	FFastLogger::LogScreen(FColor::Cyan, TEXT("PlayAnimation : %s"), *String);
	if (String.Equals(TEXT("HIGH")))
	{
		FFastLogger::LogScreen(FColor::Cyan, TEXT("PlayAnimation : High"));
		if (INT32 % 2 == 0)
		{
			TekkenAnimInstance->PlayMontageModule(TEXT("HeadHitRight"));
		}
		else
		{
			TekkenAnimInstance->PlayMontageModule(TEXT("HeadHitLeft"));
		}
	}
	else if (String.Equals(TEXT("MIDDLE")))
	{
		FFastLogger::LogScreen(FColor::Cyan, TEXT("PlayAnimation : Middle"));
		if (INT32 % 2 == 0)
		{
			TekkenAnimInstance->PlayMontageModule(TEXT("BodyHitRight"));
		}
		else
		{
			TekkenAnimInstance->PlayMontageModule(TEXT("BodyHitLeft"));
		}
	}
	else if (String.Equals(TEXT("LOW")))
	{
		FFastLogger::LogScreen(FColor::Cyan, TEXT("PlayAnimation : Low"));
		// Low에 대한 처리를 여기에 작성
	}
	else
	{
		// 그 외의 처리를 여기에 작성
	}
}

void UHitReactionNormalState::Exit()
{
	Super::Exit();
}

void UHitReactionNormalState::Enter()
{
	Super::Enter();

	HitAnimData = Me->CharacterState.HitAnimInfo;
	Me->CharacterState.HitAnimInfo = std::pair<FString, int32>(TEXT(""), -1);

	FFastLogger::LogScreen(FColor::Cyan, TEXT("HitReactionNormalState Enter"));
	
	// Hit Level과 SocketType을 이용해서 애니메이션을 찾는다.
	FString HitLevel = HitAnimData.first;
	int32 SocketID = HitAnimData.second;

	PlayAnimation(HitLevel, SocketID);
}

void UHitReactionNormalState::Update()
{
	Super::Update();

}
