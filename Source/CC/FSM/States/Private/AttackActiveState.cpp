// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/AttackActiveState.h"

FString UAttackActiveState::StateName = TEXT("ATTACK_ACTIVE");

FString UAttackActiveState::GetStateName()
{
	return StateName;
}