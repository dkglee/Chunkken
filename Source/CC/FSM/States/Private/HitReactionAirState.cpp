// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionAirState.h"

FString UHitReactionAirState::StateName = TEXT("HIT_REACTION_AIR");

FString UHitReactionAirState::GetStateName()
{
	return StateName;
}