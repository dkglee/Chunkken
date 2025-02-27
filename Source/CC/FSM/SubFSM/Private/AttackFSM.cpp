#include "AttackFSM.h"

#include "AttackActiveState.h"
#include "AttackRecoveryState.h"
#include "AttackStartupState.h"
#include "FastLogger.h"
#include "StateParser.h"
#include "TransitionParser.h"

FString UAttackFSM::StateName = TEXT("ATTACK");

void UAttackFSM::Enter(int32 ChildID)
{
	Super::Enter(ChildID);
}

void UAttackFSM::Update()
{
	Super::Update();
}

void UAttackFSM::Exit()
{
	Super::Exit();
}

FString UAttackFSM::GetStateName()
{
	return StateName;
}

void UAttackFSM::ChangeState(int32 GroupID, int32 ChildID)
{
	Super::ChangeState(GroupID, ChildID);
}

void UAttackFSM::Initialize(class ABaseCharacter* InMe, class UTekkenFSM* InOwnerFSM)
{
	Super::Initialize(InMe, InOwnerFSM);

	States.Add(UStateParser::GetStateKey(UAttackStartupState::StateName), NewObject<UAttackStartupState>(this, UAttackStartupState::StaticClass()));
	States.Add(UStateParser::GetStateKey(UAttackActiveState::StateName), NewObject<UAttackActiveState>(this, UAttackActiveState::StaticClass()));
	States.Add(UStateParser::GetStateKey(UAttackRecoveryState::StateName), NewObject<UAttackRecoveryState>(this, UAttackRecoveryState::StaticClass()));

	for (auto& [Key, Value] : States)
	{
		TransitionRules[Key].TransitionList = UTransitionParser::GetTransitionDataList(Key);
		Value->Initialize(Me, this);
	}
}
