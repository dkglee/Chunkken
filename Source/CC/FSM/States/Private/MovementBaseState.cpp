// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/MovementBaseState.h"

void UMovementBaseState::Exit()
{
	Super::Exit();
	
	bRestartMovement = true;
}

FString UMovementBaseState::GetStateName()
{
	return Super::GetStateName();
}
