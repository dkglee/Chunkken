// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/JumpStartState.h"

FString UJumpStartState::StateName = TEXT("JUMP_START");

FString UJumpStartState::GetStateName()
{
	return StateName;
}