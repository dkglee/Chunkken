// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/AttackStartupState.h"

#include "AnimationDataStruct.h"
#include "AnimParser.h"
#include "AnimUtils.h"
#include "BaseCharacter.h"
#include "FastLogger.h"
#include "MoveDataStruct.h"
#include "MoveParser.h"
#include "TekkenAnimIntance.h"

FString UAttackStartupState::StateName = TEXT("ATTACK_STARTUP");

FString UAttackStartupState::GetStateName()
{
	return StateName;
}

void UAttackStartupState::Exit()
{
	Super::Exit();

	Me->CharacterState.bFrameOver = false;
	Me->CharacterState.bAttackAvailable = false;
}

void UAttackStartupState::Enter()
{
	Super::Enter();

	FFastLogger::LogConsole(TEXT("AttackStartupState Enter"));
	
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
	int32 StartUpFrame = MoveData->StartUp;

	FFastLogger::LogConsole(TEXT("Animation %s"), *ExecutingMove.AnimationRef);

	UAnimMontage* Montage = TekkenAnimInstance->GetMontageFromName(ExecutingMove.AnimationRef);
	if (!Montage)
	{
		FFastLogger::LogConsole(TEXT("Montage is nullptr"));
		return;
	}
	float PlayRate = FAnimUtils::CalculateAnimPlayRate(StartUpFrame, Montage->GetSectionLength(0));
	FFastLogger::LogConsole(TEXT("PlayRate: %f: StartUpFrame: %d: Montage Play : %f"), PlayRate, StartUpFrame, Montage->GetSectionLength(0));
	TekkenAnimInstance->PlayMontageModule(ExecutingMove.AnimationRef, PlayRate, FName(TEXT("Startup")));
}

void UAttackStartupState::Update()
{
	Super::Update();
}
