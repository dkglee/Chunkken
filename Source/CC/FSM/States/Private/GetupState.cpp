// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/GetupState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"

FString UGetupState::StateName = TEXT("GETUP");

FString UGetupState::GetStateName()
{
	return StateName;
}

void UGetupState::Exit()
{
	Super::Exit();

	Me->CharacterState.bCanBeDamaged = true;
}

void UGetupState::Enter()
{
	Super::Enter();

	Me->CharacterState.bCanBeDamaged = false;

	FFastLogger::LogScreen(FColor::Cyan, TEXT("HitReactionKnockDown Enter"));
	
	// Airborne 애니메이션 재생
	/* TEST */
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TWeakObjectPtr<UGetupState> WeakThis = TWeakObjectPtr<UGetupState>(this);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis]()
	{
		if (WeakThis.IsValid())
		{
			UGetupState* Getup = WeakThis.Get();
			Getup->Me->CharacterState.bFrameOver = true;
		}
	}), 2.0f, false);
}

void UGetupState::Update()
{
	Super::Update();
}
