// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/AttackStartupState.h"

#include "AnimationDataStruct.h"
#include "AnimParser.h"
#include "AnimUtils.h"
#include "BaseCharacter.h"
#include "FastLogger.h"
#include "MoveDataStruct.h"
#include "MoveParser.h"
#include "SocketParser.h"
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
	PreviousSocketLocation = FVector::ZeroVector;
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

	UAnimMontage* Montage = TekkenAnimInstance->GetMontageFromName(ExecutingMove.AnimationRef);
	if (!Montage)
	{
		FFastLogger::LogConsole(TEXT("Animation: %s"), *ExecutingMove.AnimationRef);
		FFastLogger::LogConsole(TEXT("Montage is nullptr"));
		Me->CharacterState.bFrameOver = true;
		return;
	}
	float PlayRate = FAnimUtils::CalculateAnimPlayRate(StartUpFrame, Montage->GetSectionLength(0));
	PlayRate = FMath::Clamp(PlayRate, 0.0f, 3.0f);
	FFastLogger::LogConsole(TEXT("PlayRate: %f: StartUpFrame: %d: Montage Play : %f"), PlayRate, StartUpFrame, Montage->GetSectionLength(0));
	TekkenAnimInstance->PlayMontageModule(ExecutingMove.AnimationRef, PlayRate, FName(TEXT("Startup")));

	FVector LaunchDirection = {0.0f, 300.0f, 0.0f};
	if (!Me->IsLeftPlayer())
	{
		LaunchDirection *= -1;
	}
	Me->LaunchCharacter(LaunchDirection, true, true);
}

void UAttackStartupState::Update()
{
	Super::Update();

	// 소켓의 위치를 계속해서 업데이트 해줘서 이전의 위치와 비교하여 공격이 날아가는 방향을 계산한다.
	// 이펙트 방향 설정용
	int32 SocketID = Me->CurrentExecutingMove.SocketID;
	FString SocketName = USocketParser::GetSocketName(SocketID);
	if (SocketName.IsEmpty())
	{
		FFastLogger::LogConsole(TEXT("SocketName is Empty"));
		return;
	}

	// 현재 소켓 위치 가져오기
	FVector CurrentSocketLocation = Me->GetMesh()->GetSocketLocation(*SocketName);

	// 이전 위치가 초기화되지 않았다면 현재 위치로 설정 (첫 프레임)
	if (PreviousSocketLocation.IsZero())
	{
		PreviousSocketLocation = CurrentSocketLocation;
	}

	// 공격 방향 벡터 = 현재 위치 - 이전 위치
	FVector AttackDirection = CurrentSocketLocation - PreviousSocketLocation;

	// 방향 벡터 정규화 (길이를 1로 만듦)
	if (!AttackDirection.IsNearlyZero()) // 벡터가 거의 0이 아닐 때만 정규화
	{
		AttackDirection.Normalize();
	}

	// 캐릭터의 공격 방향 저장
	Me->CharacterState.AttackDirection = AttackDirection;

	// 이전 소켓 위치 갱신 (다음 프레임을 위해 저장)
	PreviousSocketLocation = CurrentSocketLocation;
}
