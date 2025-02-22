// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionBaseState.h"

#include "BaseCharacter.h"

FString UHitReactionBaseState::GetStateName()
{
	return Super::GetStateName();
}

void UHitReactionBaseState::Exit()
{
	Super::Exit();
	
	Me->CharacterState.bFrameOver = false;
	Me->CharacterState.HitStun = -1;
	Me->ClearMoveSetForce();
}

void UHitReactionBaseState::Enter()
{
	Super::Enter();

	Me->CharacterState.HitReaction = "";
	Me->CharacterState.bFrameOver = false;
	Me->ClearMoveSetForce();
}

void UHitReactionBaseState::Update()
{
	Super::Update();
}
