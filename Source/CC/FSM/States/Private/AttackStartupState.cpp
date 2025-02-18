// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/AttackStartupState.h"

FString UAttackStartupState::StateName = TEXT("ATTACK_STARTUP");

FString UAttackStartupState::GetStateName()
{
	return StateName;
}
