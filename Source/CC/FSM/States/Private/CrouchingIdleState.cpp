// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/CrouchingIdleState.h"

FString UCrouchingIdleState::StateName = TEXT("CROUCHING_IDLE");

FString UCrouchingIdleState::GetStateName()
{
	return StateName;
}