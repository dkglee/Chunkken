// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/TekkenAnimInstance/Public/TekkenAnimIntance.h"

#include "BaseCharacter.h"
#include "BaseState.h"
#include "CameraManager.h"
#include "FastLogger.h"
#include "SubFSM.h"
#include "Kismet/GameplayStatics.h"

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
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SteveDuckingBodyBlow
	(TEXT("/Game/Animations/Montages/Tekken_RightHook_Montage.Tekken_RightHook_Montage"));
	if (SteveDuckingBodyBlow.Succeeded())
	{
		MontageMap.Add(TEXT("DuckingBodyBlow"), SteveDuckingBodyBlow.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ConquerorCombo1
	(TEXT("/Game/Animations/Montages/Tekken_ConquerorComb1_Montage.Tekken_ConquerorComb1_Montage"));
	if (ConquerorCombo1.Succeeded())
	{
		MontageMap.Add(TEXT("ConquerorCombo1"), ConquerorCombo1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ConquerorComboRightHook1
	(TEXT("/Game/Animations/Montages/Tekken_ConquerorCombHook_Montage.Tekken_ConquerorCombHook_Montage"));
	if (ConquerorComboRightHook1.Succeeded())
	{
		MontageMap.Add(TEXT("ConquerorComboRightHook1"), ConquerorComboRightHook1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HeadHitLeft
	(TEXT("/Game/Animations/Montages/Tekken_Head_Hit_Left_Montage.Tekken_Head_Hit_Left_Montage"));
	if (HeadHitLeft.Succeeded())
	{
		MontageMap.Add(TEXT("HeadHitLeft"), HeadHitLeft.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HeadHitRight
	(TEXT("/Game/Animations/Montages/Tekken_Head_Hit_Right_Montage.Tekken_Head_Hit_Right_Montage"));
	if (HeadHitRight.Succeeded())
	{
		MontageMap.Add(TEXT("HeadHitRight"), HeadHitRight.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BodyHitLeft
	(TEXT("/Game/Animations/Montages/Tekken_Hit_Body_Left_Montage.Tekken_Hit_Body_Left_Montage"));
	if (BodyHitLeft.Succeeded())
	{
		MontageMap.Add(TEXT("BodyHitLeft"), BodyHitLeft.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BodyHitRight
	(TEXT("/Game/Animations/Montages/Tekken_Hit_Body_Right_Montage.Tekken_Hit_Body_Right_Montage"));
	if (BodyHitRight.Succeeded())
	{
		MontageMap.Add(TEXT("BodyHitRight"), BodyHitRight.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AirBornMontage
	(TEXT("/Game/Animations/Montages/Tekken_Hit_Airborne.Tekken_Hit_Airborne"));
	if (AirBornMontage.Succeeded())
	{
		MontageMap.Add(TEXT("AirBorn"), AirBornMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> GetupMontage
	(TEXT("/Game/Animations/Montages/Tekken_Get_Up_Seq_Montage.Tekken_Get_Up_Seq_Montage"));
	if (GetupMontage.Succeeded())
	{
		MontageMap.Add(TEXT("GetUp"), GetupMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> KOAnimation
	(TEXT("/Game/Animations/Montages/Tekken_Hit_Death_Seq_Montage.Tekken_Hit_Death_Seq_Montage"));
	if (KOAnimation.Succeeded())
	{
		MontageMap.Add(TEXT("KO"), KOAnimation.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightKickMontage
	(TEXT("/Game/Animations/Montages/Tekken_Mma_Kick_Montage.Tekken_Mma_Kick_Montage"));
	if (RightKickMontage.Succeeded())
	{
		MontageMap.Add(TEXT("RightKick"), RightKickMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightKickMontage2
	(TEXT("/Game/Animations/Montages/Tekken_WHEEL_KICK_Montage.Tekken_WHEEL_KICK_Montage"));
	if (RightKickMontage2.Succeeded())
	{
		MontageMap.Add(TEXT("RightKick2"), RightKickMontage2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightKickMontage3
	(TEXT("/Game/Animations/Montages/Tekken_540_kick_ROOT_MOTION_Montage.Tekken_540_kick_ROOT_MOTION_Montage"));
	if (RightKickMontage3.Succeeded())
	{
		MontageMap.Add(TEXT("RightKick3"), RightKickMontage3.Object);
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

void UTekkenAnimIntance::AnimNotify_CameraShake()
{
	if (!CameraManager)
	{
		CameraManager = Cast<ACameraManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraManager::StaticClass()));
	}
	FFastLogger::LogConsole(TEXT("CameraShake"));
	CameraManager->TriggerWeakShake(1.0f);
}

void UTekkenAnimIntance::PlayMontageModule(const FString& MontageName, float InPlayRate, FName StartSectionName)
{
	if (MontageMap.Contains(MontageName))
	{
		PlayMontage(MontageMap[MontageName], InPlayRate, StartSectionName);
	}
	else
	{
		FFastLogger::LogConsole(TEXT("MontageName is not valid"));
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
