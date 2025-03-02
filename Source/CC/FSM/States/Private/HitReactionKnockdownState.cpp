// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionKnockdownState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"
#include "TekkenAnimIntance.h"

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
	
	TekkenAnimInstance->PlayMontageModule(TEXT("KO"), 1.0f, FName("Default"));

	FVector LaunchDirection = {0.0f, 500.0f, 40.0f};
	if (Me->IsLeftPlayer())
	{
		LaunchDirection *= -1.0f;
	}
	Me->LaunchCharacter(LaunchDirection, true, true);
}

void UHitReactionKnockdownState::Update()
{
	Super::Update();
}
