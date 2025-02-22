// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionAirState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"

FString UHitReactionAirState::StateName = TEXT("HIT_REACTION_AIR");

FString UHitReactionAirState::GetStateName()
{
	return StateName;
}

void UHitReactionAirState::Exit()
{
	Super::Exit();
}

void UHitReactionAirState::Enter()
{
	Super::Enter();

	FFastLogger::LogScreen(FColor::Cyan, TEXT("HitReactionAirBorne Enter"));
	
	// Airborne 애니메이션 재생
	/* TEST */
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TWeakObjectPtr<UHitReactionAirState> WeakThis = TWeakObjectPtr<UHitReactionAirState>(this);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis]()
	{
		if (WeakThis.IsValid())
		{
			UHitReactionAirState* HitAir = WeakThis.Get();
			HitAir->Me->CharacterState.bFrameOver = true;
		}
	}), 2.0f, false);
}

void UHitReactionAirState::Update()
{
	Super::Update();
}
