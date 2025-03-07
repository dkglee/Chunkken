#include "KoFSM.h"

#include "CameraManager.h"
#include "ECameraSequence.h"
#include "TekkenCameraShake.h"

FString UKoFSM::StateName = TEXT("KO");

void UKoFSM::Enter(int32 ChildID)
{
	Super::Enter(ChildID);

	TekkenAnimInstance->PlayMontageModule(TEXT("KO"), 1.0f, FName("Default"));
	CameraManager->PlayerCameraShake(ECameraSequence::ECS_KO, 1.0f);

	FVector LaunchDirection = {0.0f, 500.0f, 40.0f};
	if (Me->IsLeftPlayer())
	{
		LaunchDirection *= -1.0f;
	}
	Me->LaunchCharacter(LaunchDirection, true, true);
}

void UKoFSM::Update()
{
	Super::Update();
}

void UKoFSM::Exit()
{
	Super::Exit();
}

FString UKoFSM::GetStateName()
{
	return Super::GetStateName();
}

void UKoFSM::ChangeState(int32 GroupID, int32 ChildID)
{
	Super::ChangeState(GroupID, ChildID);
}

void UKoFSM::Initialize(class ABaseCharacter* InMe, class UTekkenFSM* InOwnerFSM)
{
	Super::Initialize(InMe, InOwnerFSM);
}
