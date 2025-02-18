// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/AttackStartupState.h"

#include "FastLogger.h"

FString UAttackStartupState::StateName = TEXT("ATTACK_STARTUP");

FString UAttackStartupState::GetStateName()
{
	return StateName;
}

void UAttackStartupState::Exit()
{
	Super::Exit();
}

void UAttackStartupState::Enter()
{
	Super::Enter();

	FFastLogger::LogScreen(FColor::Red, TEXT("Enter AttackStartupState"));
}

void UAttackStartupState::Update()
{
	Super::Update();
}
