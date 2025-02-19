// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/WalkBackwardState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"
#include "TekkenAnimIntance.h"

FString UWalkBackwardState::StateName = TEXT("WALK_BACKWARD");

FString UWalkBackwardState::GetStateName()
{
	return StateName;
}

void UWalkBackwardState::Exit()
{
	Super::Exit();
}

void UWalkBackwardState::Enter()
{
	Super::Enter();
}

void UWalkBackwardState::Update()
{
	Super::Update();

	// Update에서 계속해서 실행해야 함.
	if (bRestartMovement && Me->CharacterState.bBackward)
	{
		TekkenAnimInstance->PlayMontageModule(MontageName, 1.0f, FName(TEXT("Default")));
		bRestartMovement = false;
		Me->CharacterState.bFrameOver = false;
	}
	else if (bRestartMovement)
	{
		Me->CharacterState.bFrameOver = true;
	}

	if (!Me->CharacterState.bFrameOver)
	{
		// 이동 로직
		Me->AddMovementInput(-Me->GetActorForwardVector(), 0.1f);
	}
}
