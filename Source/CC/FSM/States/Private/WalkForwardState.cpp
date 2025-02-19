// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/WalkForwardState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"
#include "TekkenAnimIntance.h"

FString UWalkForwardState::StateName = TEXT("WALK_FORWARD");

FString UWalkForwardState::GetStateName()
{
	return StateName;
}

UWalkForwardState::UWalkForwardState()
{
	
}

void UWalkForwardState::Exit()
{
	Super::Exit();

	Me->CharacterState.bFrameOver = false;
}

void UWalkForwardState::Enter()
{
	Super::Enter();

	FFastLogger::LogScreen(FColor::Red, TEXT("Enter WalkForwardState"));
	MoveSpeed = 0.0f;
}

void UWalkForwardState::Update()
{
	Super::Update();

	// Update에서 계속해서 실행해야 함.
	// PlayMontage가 실행되면 그만큼 움직이게 하고 싶음. : 이때는 bFrameOver를 false로 바꿔서 전이가 일어나지 않게 함.
	// 이동이 끝나면 즉, bRestartMovement가 true가 되고 해당 상태에서 다른 상태로 전이가 가능하게 함. // 이때는 bFrameOver를 true로 바꿔서 전이가 일어나게 함.
	if (bRestartMovement && Me->CharacterState.bForward)
	{
		TekkenAnimInstance->PlayMontageModule(MontageName, 1.0f, FName(TEXT("Default")));
		bRestartMovement = false;
		Me->CharacterState.bFrameOver = false;

		MoveSpeed = 0.0f;
	}
	else if (bRestartMovement)
	{
		Me->CharacterState.bFrameOver = true;
	}

	if (!Me->CharacterState.bFrameOver)
	{
		// 이동 로직
		MoveSpeed += SpeedScale;
		MoveSpeed = FMath::Clamp(MoveSpeed, 0.0f, 0.3f);
		float TempSpeed = MoveSpeed;
		if (MoveSpeed >= 0.3f)
		{
			TempSpeed = 0.15f;
		}
		Me->AddMovementInput(Me->GetActorForwardVector(), TempSpeed);
	}
}
