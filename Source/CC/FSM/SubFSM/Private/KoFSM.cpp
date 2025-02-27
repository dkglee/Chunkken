#include "KoFSM.h"

#include "CameraManager.h"

FString UKoFSM::StateName = TEXT("KO");

void UKoFSM::Enter(int32 ChildID)
{
	Super::Enter(ChildID);

	TekkenAnimInstance->PlayMontageModule(TEXT("KO"), 1.0f, FName("Default"));
	CameraManager->TriggerWeakShake(1.0f);
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
