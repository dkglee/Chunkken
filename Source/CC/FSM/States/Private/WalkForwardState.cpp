// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/WalkForwardState.h"

#include "FastLogger.h"

FString UWalkForwardState::StateName = TEXT("WALK_FORWARD");

FString UWalkForwardState::GetStateName()
{
	return StateName;
}

void UWalkForwardState::Exit()
{
	Super::Exit();
}

void UWalkForwardState::Enter()
{
	Super::Enter();

	FFastLogger::LogScreen(FColor::Red, TEXT("Enter WalkForwardState"));
}

void UWalkForwardState::Update()
{
	Super::Update();
}
