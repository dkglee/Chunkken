// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/GetupState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"
#include "TekkenAnimIntance.h"

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

	// Airborne 애니메이션 재생
	TekkenAnimInstance->PlayMontageModule(TEXT("GetUp"), 1.0f, FName("Default"));
}

void UGetupState::Update()
{
	Super::Update();
}
