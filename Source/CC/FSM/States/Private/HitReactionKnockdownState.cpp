// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionKnockdownState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"

FString UHitReactionKnockdownState::StateName = TEXT("HIT_REACTION_KNOCKDOWN");

FString UHitReactionKnockdownState::GetStateName()
{
	return StateName;
}

void UHitReactionKnockdownState::Exit()
{
	Super::Exit();
}

void UHitReactionKnockdownState::Enter()
{
	Super::Enter();

	Me->CharacterState.bCanBeDamaged = false;
	
	FFastLogger::LogScreen(FColor::Cyan, TEXT("HitReactionKnockDown Enter"));
	
	// Airborne 애니메이션 재생
	/* TEST */
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TWeakObjectPtr<UHitReactionKnockdownState> WeakThis = TWeakObjectPtr<UHitReactionKnockdownState>(this);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis]()
	{
		if (WeakThis.IsValid())
		{
			UHitReactionKnockdownState* KnockDown = WeakThis.Get();
			KnockDown->Me->CharacterState.bFrameOver = true;
		}
	}), 2.0f, false);
}

void UHitReactionKnockdownState::Update()
{
	Super::Update();
}
