// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/JumpStartState.h"

#include "TekkenAnimIntance.h"

FString UJumpStartState::StateName = TEXT("JUMP_START");

FString UJumpStartState::GetStateName()
{
	return StateName;
}

void UJumpStartState::Exit()
{
	Super::Exit();
}

void UJumpStartState::Enter()
{
	Super::Enter();

	TekkenAnimInstance->PlayMontageModule(MontageName, 1.0f, FName(TEXT("Default")));
}

void UJumpStartState::Update()
{
	Super::Update();
}
