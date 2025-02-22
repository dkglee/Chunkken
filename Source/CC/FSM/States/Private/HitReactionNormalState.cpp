// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionNormalState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"

FString UHitReactionNormalState::StateName = TEXT("HIT_REACTION_NORMAL");

FString UHitReactionNormalState::GetStateName()
{
	return StateName;
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

	// SocketID = Odd : Left | Even : Right // 애니메이션 재생

	
	/* TEST */
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TWeakObjectPtr<UHitReactionNormalState> WeakThis = TWeakObjectPtr<UHitReactionNormalState>(this);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis]()
	{
		if (WeakThis.IsValid())
		{
			UHitReactionNormalState* HitReactionNormalState = WeakThis.Get();
			HitReactionNormalState->Me->CharacterState.bFrameOver = true;
		}
	}), 2.0f, false);
}

void UHitReactionNormalState::Update()
{
	Super::Update();

}
