#include "JumpFSM.h"

#include "BaseState.h"
#include "JumpStartState.h"
#include "StateParser.h"
#include "TekkenFSM.h"
#include "TransitionParser.h"

FString UJumpFSM::StateName = TEXT("JUMP");

void UJumpFSM::Enter(int32 ChildID)
{
	Super::Enter(ChildID);
}

void UJumpFSM::Update()
{
	Super::Update();
}

void UJumpFSM::Exit()
{
	Super::Exit();
}

FString UJumpFSM::GetStateName()
{
	return StateName;
}

void UJumpFSM::ChangeState(int32 GroupID, int32 ChildID)
{
	Super::ChangeState(GroupID, ChildID);
}

void UJumpFSM::Initialize(class ABaseCharacter* InMe, class UTekkenFSM* InOwnerFSM)
{
	Super::Initialize(InMe, InOwnerFSM);

	States.Add(UStateParser::GetStateKey(UJumpStartState::StateName), NewObject<UJumpStartState>(this, UJumpStartState::StaticClass()));

	for (auto& [Key, Value] : States)
	{
		TransitionRules[Key].TransitionList = UTransitionParser::GetTransitionDataList(Key);
		Value->Initialize(Me, this);
	}
}
