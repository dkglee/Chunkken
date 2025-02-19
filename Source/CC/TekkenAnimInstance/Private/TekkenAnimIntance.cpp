// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/TekkenAnimInstance/Public/TekkenAnimIntance.h"

#include "BaseCharacter.h"
#include "BaseState.h"
#include "FastLogger.h"
#include "SubFSM.h"

UTekkenAnimIntance::UTekkenAnimIntance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> IdleMontage
	(TEXT("/Game/Animations/Montages/Tekken_Idle_Montage.Tekken_Idle_Montage"));
	if (IdleMontage.Succeeded())
	{
		MontageMap.Add(TEXT("IDLE"), IdleMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MoveForwardMontage
	(TEXT("/Game/Animations/Montages/Tekken_MOVE_FORWARD_Montage.Tekken_MOVE_FORWARD_Montage"));
	if (MoveForwardMontage.Succeeded())
	{
		MontageMap.Add(TEXT("MOVE_FORWARD"), MoveForwardMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MoveBackwardMontage
	(TEXT("/Game/Animations/Montages/Tekken_MOVE_BACK_Montage.Tekken_MOVE_BACK_Montage"));
	if (MoveBackwardMontage.Succeeded())
	{
		MontageMap.Add(TEXT("MOVE_BACKWARD"), MoveBackwardMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> JumpMontage
	(TEXT("/Game/Animations/Montages/Tekken_Jump_Montage.Tekken_Jump_Montage"));
	if (JumpMontage.Succeeded())
	{
		MontageMap.Add(TEXT("JUMP"), JumpMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SteveLeftPunchMontage
	(TEXT("/Game/Animations/Montages/Tekken_Left_Punch_Montage.Tekken_Left_Punch_Montage"));
	if (SteveLeftPunchMontage.Succeeded())
	{
		MontageMap.Add(TEXT("Jab"), SteveLeftPunchMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SteveRightPunchMontage
	(TEXT("/Game/Animations/Montages/Tekken_RightPunch_Montage.Tekken_RightPunch_Montage"));
	if (SteveRightPunchMontage.Succeeded())
	{
		MontageMap.Add(TEXT("RightJab"), SteveRightPunchMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SteveVanguardMontage
	(TEXT("/Game/Animations/Montages/Tekken_Hook_Montage.Tekken_Hook_Montage"));
	if (SteveVanguardMontage.Succeeded())
	{
		MontageMap.Add(TEXT("VanguardRush1"), SteveVanguardMontage.Object);
	}
	
}

void UTekkenAnimIntance::AnimNotify_RestartMovement()
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(UAnimInstance::TryGetPawnOwner());
	if (BaseCharacter)
	{
		UBaseState* CurrentState = BaseCharacter->GetCurrentState();
		if (CurrentState)
		{
			CurrentState->SetRestartMovement(true);
		} 
	}
}

void UTekkenAnimIntance::AnimNotify_ResetFrame()
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(UAnimInstance::TryGetPawnOwner());
	if (BaseCharacter)
	{
		BaseCharacter->CharacterState.bFrameOver = true;
	}
}

void UTekkenAnimIntance::AnimNotify_ComboRestart()
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(UAnimInstance::TryGetPawnOwner());
	if (BaseCharacter)
	{
		BaseCharacter->CharacterState.bAttackAvailable = true;
	}
}

void UTekkenAnimIntance::PlayMontageModule(const FString& MontageName, float InPlayRate, FName StartSectionName)
{
	if (MontageMap.Contains(MontageName))
	{
		FFastLogger::LogScreen(FColor::Blue, TEXT("Play Montage: %s"), *MontageName);
		PlayMontage(MontageMap[MontageName], InPlayRate, StartSectionName);
	}
}

class UAnimMontage* UTekkenAnimIntance::GetMontageFromName(const FString& String)
{
	if (MontageMap.Contains(String))
	{
		return MontageMap[String];
	}
	return nullptr;
}
