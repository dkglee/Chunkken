// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/TekkenAnimInstance/Public/TekkenAnimIntance.h"

#include "BaseCharacter.h"
#include "BaseState.h"
#include "CameraManager.h"
#include "ECameraSequence.h"
#include "FastLogger.h"
#include "MyPlayerController.h"
#include "SubFSM.h"
#include "TekkenCameraShake.h"
#include "Kismet/GameplayStatics.h"

UTekkenAnimIntance::UTekkenAnimIntance()
{
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
	if (!CameraShakeManager)
	{
		AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		CameraShakeManager = MyPlayerController->GetCameraShakeManager();
	}
	CameraShakeManager->PlayerCameraShake(ECameraSequence::ECS_Airbone, 1.0f);
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
