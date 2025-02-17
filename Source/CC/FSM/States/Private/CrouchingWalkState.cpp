// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/CrouchingWalkState.h"

FString UCrouchingWalkState::StateName = TEXT("CROUCHING_WALK");

FString UCrouchingWalkState::GetStateName()
{
	return StateName;
}