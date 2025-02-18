#include "MovementFSM.h"

#include "StateParser.h"
#include "TekkenFSM.h"
#include "TransitionParser.h"
#include "WalkBackwardState.h"
#include "WalkForwardState.h"

FString UMovementFSM::StateName = TEXT("MOVEMENT");

void UMovementFSM::Enter(int32 ChildID)
{
	Super::Enter(ChildID);
}

void UMovementFSM::Update()
{
	Super::Update();
}

void UMovementFSM::Exit()
{
	Super::Exit();
}

FString UMovementFSM::GetStateName()
{
	return StateName;
}

void UMovementFSM::ChangeState(int32 GroupID, int32 ChildID)
{
	Super::ChangeState(GroupID, ChildID);
}

void UMovementFSM::Initialize(class ABaseCharacter* InMe, class UTekkenFSM* InOwnerFSM)
{
	Super::Initialize(InMe, InOwnerFSM);

	States.Add(UStateParser::GetStateKey(UWalkForwardState::StateName), NewObject<UWalkForwardState>(this, UWalkForwardState::StaticClass()));
	States.Add(UStateParser::GetStateKey(UWalkBackwardState::StateName), NewObject<UWalkBackwardState>(this, UWalkBackwardState::StaticClass()));

	for (auto& [Key, Value] : States)
	{
		TransitionRules[Key].TransitionList = UTransitionParser::GetTransitionDataList(Key);
		Value->Initialize(Me, this);
	}
}

