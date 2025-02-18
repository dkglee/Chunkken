// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionKnockdownState.h"

FString UHitReactionKnockdownState::StateName = TEXT("HIT_REACTION_KNOCKDOWN");

FString UHitReactionKnockdownState::GetStateName()
{
	return StateName;
}