// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionAirState.h"

#include "BaseCharacter.h"
#include "FastLogger.h"
#include "TekkenAnimIntance.h"
#include "GameFramework/CharacterMovementComponent.h"

FString UHitReactionAirState::StateName = TEXT("HIT_REACTION_AIR");

FString UHitReactionAirState::GetStateName()
{
	return StateName;
}

void UHitReactionAirState::Exit()
{
	Super::Exit();

	bIsGrounded = false;
	CurrentFrameAirBorne = 0;
	Location = FVector::ZeroVector;
	Me->CharacterState.bGround = true;
}

void UHitReactionAirState::Enter()
{
	Super::Enter();

	FFastLogger::LogScreen(FColor::Cyan, TEXT("HitReactionAirBorne Enter"));
	
	// Airborne 애니메이션 재생
	// 1. 공중에 띄움 // 2. 애니메이션 재생
	// 현재 위치 가져오기
	CurrentFrameAirBorne = 0;

	bool bIsLeft = Me->IsLeftPlayer();
	Location = Me->GetActorLocation();
	Location.Z = MaxHeight;
	Location.Y = bIsLeft ? Location.Y - 25.0f : Location.Y + 25.0f;
	Me->SetActorLocation(Location);

	Me->CharacterState.bGround = false;

	// 애니메이션 재생
	TekkenAnimInstance->PlayMontageModule(TEXT("AirBorn"), 1.0f, FName("Default"));
}

void UHitReactionAirState::Update()
{
	Super::Update();

	CurrentFrameAirBorne++;
	if (CurrentFrameAirBorne < MaxFrameAirBorne)
	{
		Me->SetActorLocation(Location);
	}
	
	// 2. 공중에서 떨어짐 (땅에 닿으면 애니메이션의 KnockDown 부분을 재생함)
	if (Me->GetCharacterMovement()->IsMovingOnGround() && !bIsGrounded)
	{
		bIsGrounded = true;
		TekkenAnimInstance->PlayMontageModule(TEXT("AirBorn"), 1.0f, FName("KnockDown"));
		// Getup으로 가야함
		Me->CharacterState.bCanBeDamaged = false;
		Me->CharacterState.bGround = true;
	}
}
