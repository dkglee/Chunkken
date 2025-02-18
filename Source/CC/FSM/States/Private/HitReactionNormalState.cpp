// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionNormalState.h"

FString UHitReactionNormalState::StateName = TEXT("HIT_REACTION_NORMAL");

FString UHitReactionNormalState::GetStateName()
{
	return StateName;
}