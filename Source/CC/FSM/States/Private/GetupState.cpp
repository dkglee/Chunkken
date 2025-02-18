// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/GetupState.h"

FString UGetupState::StateName = TEXT("GETUP");

FString UGetupState::GetStateName()
{
	return StateName;
}