// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/AttackRecoveryState.h"

FString UAttackRecoveryState::StateName = TEXT("ATTACK_RECOVERY");

FString UAttackRecoveryState::GetStateName()
{
	return StateName;
}