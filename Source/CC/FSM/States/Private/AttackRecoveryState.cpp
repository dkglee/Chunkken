// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/AttackRecoveryState.h"

#include "AnimUtils.h"
#include "BaseCharacter.h"
#include "FastLogger.h"
#include "MoveParser.h"
#include "TekkenAnimIntance.h"

struct FMoveDataStruct;
FString UAttackRecoveryState::StateName = TEXT("ATTACK_RECOVERY");

FString UAttackRecoveryState::GetStateName()
{
	return StateName;
}

void UAttackRecoveryState::Exit()
{
	Super::Exit();

	// TODO: 검증 필요
	Me->CharacterState.bFrameOver = false;
	// Me->CharacterState.bAttackAvailable = false;
	Me->bResetMoveSet = true;
}

void UAttackRecoveryState::Enter()
{
	Super::Enter();

	FFastLogger::LogConsole(TEXT("AttackRecoveryState Enter"));
	
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
	int32 RecvoryFrame = MoveData->Recovery;

	UAnimMontage* Montage = TekkenAnimInstance->GetMontageFromName(ExecutingMove.AnimationRef);
	if (!Montage)
	{
		FFastLogger::LogConsole(TEXT("Montage is nullptr"));
		Me->CharacterState.bFrameOver = true;
		Me->CharacterState.bAttackAvailable = true;
		return;
	}
	float PlayRate = FAnimUtils::CalculateAnimPlayRate(RecvoryFrame, Montage->GetSectionLength(2));
	FFastLogger::LogConsole(TEXT("PlayRate: %f: Recovery: %d: Montage Play : %f"), PlayRate, RecvoryFrame, Montage->GetSectionLength(2));
	TekkenAnimInstance->PlayMontageModule(ExecutingMove.AnimationRef, PlayRate, FName(TEXT("Recovery")));
}

void UAttackRecoveryState::Update()
{
	Super::Update();
}
