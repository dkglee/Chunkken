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
	
	FFastLogger::LogScreen(FColor::Cyan, TEXT("HitReactionKnockDown Enter"));
	TekkenAnimInstance->PlayMontageModule(TEXT("KO"), 1.0f, FName("Default"));
}

void UHitReactionKnockdownState::Update()
{
	Super::Update();
}
