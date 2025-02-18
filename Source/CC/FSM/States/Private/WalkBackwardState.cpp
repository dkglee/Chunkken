// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/WalkBackwardState.h"

FString UWalkBackwardState::StateName = TEXT("WALK_BACKWARD");

FString UWalkBackwardState::GetStateName()
{
	return StateName;
}