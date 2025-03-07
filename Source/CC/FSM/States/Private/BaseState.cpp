// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseState.h"

#include "BaseCharacter.h"
#include "CameraManager.h"
#include "MyPlayerController.h"
#include "TekkenAnimIntance.h"
#include "Kismet/GameplayStatics.h"

void UBaseState::Initialize(ABaseCharacter* InMe, USubFSM* InOwnerFSM)
{
	Me = InMe;
	OwnerFSM = InOwnerFSM;
	TekkenAnimInstance = Cast<UTekkenAnimIntance>(Me->GetMesh()->GetAnimInstance());
	CameraManager = Cast<ACameraManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraManager::StaticClass()));
	AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(Me->GetWorld(), 0));
	CameraShakeManager = MyPlayerController->GetCameraShakeManager();
}

void UBaseState::SetRestartMovement(bool bFlag)
{
	bRestartMovement = bFlag;
}
