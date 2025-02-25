// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/JumpStartState.h"

#include "BaseCharacter.h"
#include "TekkenAnimIntance.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	Me->Jump();
	Me->CharacterState.bGround = false;
	TekkenAnimInstance->PlayMontageModule(MontageName, 1.0f, FName(TEXT("Default")));
}

void UJumpStartState::Update()
{
	Super::Update();

	Me->CharacterState.bGround = !(Me->GetCharacterMovement()->IsFalling());
}
