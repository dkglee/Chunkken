// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/WalkForwardState.h"

FString UWalkForwardState::StateName = TEXT("WALK_FORWARD");

FString UWalkForwardState::GetStateName()
{
	return StateName;
}