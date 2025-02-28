// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/HitReactionAirState.h"

#include "BaseCharacter.h"
#include "CameraManager.h"
#include "EasingAlphaBlend.h"
#include "ECameraSequence.h"
#include "FastLogger.h"
#include "TekkenAnimIntance.h"
#include "TekkenCameraShake.h"
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
	bMaxHeight = false;
	CurrentFrameAirBorne = 0;
	Location = FVector::ZeroVector;
	Me->CharacterState.bGround = true;
}

void UHitReactionAirState::Enter()
{
	Super::Enter();

	bMaxHeight = false;
	
	CurrentFrameAirBorne = 0;

	bool bIsLeft = Me->IsLeftPlayer();

	// 최종 높이 설정
	Location = Me->GetActorLocation();
	// Location.Z = MaxHeight;
	Location.Z = 0.0f;
	Location.Y = bIsLeft ? Location.Y - 40.0f : Location.Y + 40.0f;

	// 공중 상태로 변경
	Me->CharacterState.bGround = false;

	// 애니메이션 재생
	TekkenAnimInstance->PlayMontageModule(TEXT("AirBorn"), 1.0f, FName("Default"));
}

void UHitReactionAirState::Update()
{
	Super::Update();

	CurrentFrameAirBorne++;
	if (CurrentFrameAirBorne < MaxFrameAirBorne && !bMaxHeight)
	{
		// FVector InterpLocation = FEasingAlphaBlend::EasingVectorBlend(Me->GetActorLocation(), Location, (float)CurrentFrameAirBorne / (float)MaxFrameAirBorne, 1.0f, bMaxHeight);
		// Me->SetActorLocation(InterpLocation, true);
		FFastLogger::LogConsole(TEXT("CurrentFrameAirBorne : %d, Me: %s, Target: %s"), CurrentFrameAirBorne, *Me->GetActorLocation().ToString(), *Location.ToString());
		float Delta = (float)CurrentFrameAirBorne / (float)MaxFrameAirBorne;
		FVector InterpLocation = FMath::VInterpTo(Me->GetActorLocation(), Location, Delta, 2.0f);
		if (FMath::IsNearlyEqual(InterpLocation.Z, Location.Z, 1.0f))
		{
			bMaxHeight = true;
		}
		Me->SetActorLocation(InterpLocation);
	}
	
	// 2. 공중에서 떨어짐 (땅에 닿으면 애니메이션의 KnockDown 부분을 재생함)
	if (Me->GetCharacterMovement()->IsMovingOnGround() && !bIsGrounded)
	{
		bIsGrounded = true;
		TekkenAnimInstance->PlayMontageModule(TEXT("AirBorn"), 1.0f, FName("KnockDown"));
		// Getup으로 가야함
		Me->CharacterState.bCanBeDamaged = false;
		Me->CharacterState.bGround = true;
		CameraShakeManager->PlayerCameraShake(ECameraSequence::ECS_Airbone, 1.0f);
	}
}
