// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/AttackActiveState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"
#include "MoveDataStruct.h"
#include "MoveParser.h"

FString UAttackActiveState::StateName = TEXT("ATTACK_ACTIVE");

FString UAttackActiveState::GetStateName()
{
	return StateName;
}

void UAttackActiveState::Exit()
{
	Super::Exit();

	EndCount = 0;

	Me->CharacterState.bFrameOver = false;
	Me->CharacterState.bAttackAvailable = false;

	// 충돌 비활성화 해줘야 함
	// Me->ResetCollision();
}

void UAttackActiveState::Enter()
{
	Super::Enter();

	FFastLogger::LogConsole(TEXT("AttackActiveState Enter"));
	
	EndCount = 0;

	Me->CharacterState.bFrameOver = false;
	Me->CharacterState.bAttackAvailable = false;
	Me->bResetMoveSet = false;

	FExecutingMove ExecutingMove = Me->CurrentExecutingMove;
	const FMoveDataStruct* MoveData = UMoveParser::GetMoveDataByMoveID(ExecutingMove.MoveID);
	if (!MoveData)
	{
		FFastLogger::LogConsole(TEXT("MoveData is nullptr"));
		return;
	}
	EndFrame = MoveData->ActiveFrames;

	// 충돌 활성화 해줘야 함
	// Me->SetCollision();
}

void UAttackActiveState::Update()
{
	Super::Update();

	if (EndCount == EndFrame)
	{
		Me->CharacterState.bFrameOver = true;
	}
	else
	{
		EndCount++;
	}
}
