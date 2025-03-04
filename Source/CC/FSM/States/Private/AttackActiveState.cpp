// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/AttackActiveState.h"

#include "BaseCharacter.h"
#include "DamageComponent.h"
#include "FastLogger.h"
#include "MoveDataStruct.h"
#include "MoveParser.h"
#include "SocketParser.h"
#include "TekkenAnimIntance.h"

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
	bHit = false;

	// 충돌 비활성화 해줘야 함
	// Me->ResetCollision();
}

void UAttackActiveState::Enter()
{
	Super::Enter();

	bHit = false;

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

	UAnimMontage* Montage = TekkenAnimInstance->GetMontageFromName(ExecutingMove.AnimationRef);
	if (!Montage)
	{
		FFastLogger::LogConsole(TEXT("Animation: %s"), *ExecutingMove.AnimationRef);
		FFastLogger::LogConsole(TEXT("Montage is nullptr"));
		Me->CharacterState.bFrameOver = true;
		return;
	}
	
	EndFrame = MoveData->ActiveFrames;
}

void UAttackActiveState::Update()
{
	Super::Update();

	if (EndCount == EndFrame)
	{
		Me->CharacterState.bFrameOver = true;
		return ;
	}
	
	EndCount++;

	if (bHit != false)
	{
		return ;
	}
	
	UDamageComponent* DamageComponent = Me->GetDamageComponent();
	if (!DamageComponent)
	{
		FFastLogger::LogConsole(TEXT("DamageComponent is nullptr : %p"), Me);
		return;
	}

	int32 SocketID = Me->CurrentExecutingMove.SocketID;
	FString SocketName = USocketParser::GetSocketName(SocketID);
	if (SocketName.IsEmpty())
	{
		FFastLogger::LogConsole(TEXT("SocketName is Empty"));
		return;
	}
	
	bHit = DamageComponent->DetectCollision(SocketName);
}
