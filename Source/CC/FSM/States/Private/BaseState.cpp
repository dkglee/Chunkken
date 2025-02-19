// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/FSM/States/Public/BaseState.h"

#include "BaseCharacter.h"
#include "TekkenAnimIntance.h"

void UBaseState::Initialize(class ABaseCharacter* InMe, class USubFSM* InOwnerFSM)
{
	Me = InMe;
	OwnerFSM = InOwnerFSM;
	TekkenAnimInstance = Cast<UTekkenAnimIntance>(Me->GetMesh()->GetAnimInstance());
}

void UBaseState::SetRestartMovement(bool bFlag)
{
	bRestartMovement = bFlag;
}
