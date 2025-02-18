#include "HitReactionFSM.h"

#include "GetupState.h"
#include "HitReactionAirState.h"
#include "HitReactionKnockdownState.h"
#include "HitReactionNormalState.h"
#include "StateParser.h"
#include "TransitionParser.h"

FString UHitReactionFSM::StateName = TEXT("HIT_REACTION");

void UHitReactionFSM::Enter(int32 ChildID)
{
	Super::Enter(ChildID);
}

void UHitReactionFSM::Update()
{
	Super::Update();
}

void UHitReactionFSM::Exit()
{
	Super::Exit();
}

FString UHitReactionFSM::GetStateName()
{
	return StateName;
}

void UHitReactionFSM::ChangeState(int32 GroupID, int32 ChildID)
{
	Super::ChangeState(GroupID, ChildID);
}

void UHitReactionFSM::Initialize(class ABaseCharacter* InMe, class UTekkenFSM* InOwnerFSM)
{
	Super::Initialize(InMe, InOwnerFSM);

	States.Add(UStateParser::GetStateKey(UHitReactionNormalState::StateName), NewObject<UHitReactionNormalState>(this, UHitReactionNormalState::StaticClass()));
	States.Add(UStateParser::GetStateKey(UHitReactionAirState::StateName), NewObject<UHitReactionAirState>(this, UHitReactionAirState::StaticClass()));
	States.Add(UStateParser::GetStateKey(UHitReactionKnockdownState::StateName), NewObject<UHitReactionKnockdownState>(this, UHitReactionKnockdownState::StaticClass()));
	States.Add(UStateParser::GetStateKey(UGetupState::StateName), NewObject<UGetupState>(this, UGetupState::StaticClass()));

	for (auto& [Key, Value] : States)
	{
		TransitionRules[Key].TransitionList = UTransitionParser::GetTransitionDataList(Key);
		Value->Initialize(Me, this);
	}
}
