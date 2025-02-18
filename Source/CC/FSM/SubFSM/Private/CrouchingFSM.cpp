#include "CrouchingFSM.h"

#include "BaseState.h"
#include "CrouchingIdleState.h"
#include "CrouchingWalkState.h"
#include "StateParser.h"
#include "TekkenFSM.h"
#include "TransitionParser.h"

FString UCrouchingFSM::StateName = TEXT("CROUCHING");

void UCrouchingFSM::Enter(int32 ChildID)
{
	Super::Enter(ChildID);
}

void UCrouchingFSM::Update()
{
	Super::Update();
}

void UCrouchingFSM::Exit()
{
	Super::Exit();
}

FString UCrouchingFSM::GetStateName()
{
	return StateName;
}

void UCrouchingFSM::ChangeState(int32 GroupID, int32 ChildID)
{
	Super::ChangeState(GroupID, ChildID);
}

void UCrouchingFSM::Initialize(class ABaseCharacter* InMe, class UTekkenFSM* InOwnerFSM)
{
	Super::Initialize(InMe, InOwnerFSM);

	States.Add(UStateParser::GetStateKey(UCrouchingIdleState::StateName), NewObject<UCrouchingIdleState>(this, UCrouchingIdleState::StaticClass()));
	States.Add(UStateParser::GetStateKey(UCrouchingWalkState::StateName), NewObject<UCrouchingWalkState>(this, UCrouchingWalkState::StaticClass()));

	for (auto& [Key, Value] : States)
	{
		TransitionRules[Key].TransitionList = UTransitionParser::GetTransitionDataList(Key);
		Value->Initialize(Me, this);
	}
}
