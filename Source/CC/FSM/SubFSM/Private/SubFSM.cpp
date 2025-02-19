#include "SubFSM.h"

#include "BaseCharacter.h"
#include "BaseState.h"
#include "CharacterState.h"
#include "ConditionManager.h"
#include "FastLogger.h"
#include "StateParser.h"
#include "TekkenFSM.h"

void USubFSM::Enter(int32 ChildID)
{
	if (!States.Contains(ChildID))
	{
		CurrentState = nullptr;
		return ;
	}
	CurrentState = States[ChildID];
	CurrentState->Enter();
	FFastLogger::LogConsole(TEXT("Enter: %s"), *CurrentState->GetStateName());
}

void USubFSM::Update()
{
	// FFastLogger::LogConsole(TEXT("%s"), *GetStateName());
	if (!CurrentState)
	{
		return ;
	}
	// FFastLogger::LogConsole(TEXT("%s"), *CurrentState->GetStateName());

	std::pair<int32, int32> Result;
	if (CheckTransitionList(Result))
	{
		ChangeState(Result.first, Result.second);
		return ;
	}
	CurrentState->Update();
}

void USubFSM::Exit()
{
	if (!CurrentState)
	{
		return ;
	}
	CurrentState->Exit();
}

void USubFSM::ChangeState(int32 GroupID, int32 ChildID)
{
	if (GroupID == -1)
	{
		OwnerFSM->ChangeSubFSM(GroupID, ChildID);
		return ;
	}
	
	if (CurrentState)
	{
		CurrentState->Exit();
	}
	if (!States.Contains(ChildID))
	{
		CurrentState = nullptr;
		return ;
	}
	CurrentState = States[ChildID];
	CurrentState->Enter();
}

class UBaseState* USubFSM::GetCurrentState()
{
	return CurrentState;
}

bool USubFSM::CheckTransitionList(std::pair<int32, int32>& Result)
{
	FTransitionListDataStruct* HighestTransition = nullptr;

	// 여기서 모든 조건들을 검사하고 만약 조건이 맞는 것이 여러개라면 우선 순위에 따라서 실행한다.
	std::vector<FTransitionListDataStruct*> TransitionList = TransitionRules[UStateParser::GetStateKey(CurrentState->GetStateName())].TransitionList;
	for (auto& Transition : TransitionList)
	{
		if (!ValidateCondition(Transition))
		{
			continue;
		}
		if (HighestTransition == nullptr || Transition->Priority > HighestTransition->Priority)
		{
			HighestTransition = Transition;
		}
	}

	if (!HighestTransition)
	{
		return false;
	}

	Result.first = UStateParser::GetParentStateKey(HighestTransition->ToStateID);
	Result.second = HighestTransition->ToStateID;

	return true;
}

bool USubFSM::ValidateCondition(FTransitionListDataStruct* Transition)
{
	TArray<FString> ConditionTokens = Transition->ConditionTokens;
	TMap<FString, bool> ConditionValues;
	for (auto& Token : ConditionTokens)
	{
		ConditionValues.Add(Token, false);
		ConditionValues[Token] = FConditionManager::Get().CheckCondition(FCString::Atoi(*Token), WrapJsonString());
	}
	return Transition->ConditionLogic->Evaluate(ConditionValues);
}

FString USubFSM::WrapJsonString()
{
	const FCharacterState& CharacterState = Me->CharacterState;

	// JSON 객체 생성
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	// 상태 정보를 JSON에 삽입
	JsonObject->SetBoolField("bForward", CharacterState.bForward);
	JsonObject->SetBoolField("bBackward", CharacterState.bBackward);
	JsonObject->SetBoolField("bJump", CharacterState.bJump);
	JsonObject->SetBoolField("bCrouching", CharacterState.bCrouching);
	JsonObject->SetBoolField("bAttack", CharacterState.bAttack);
	JsonObject->SetBoolField("bGround", CharacterState.bGround);
	JsonObject->SetBoolField("bAttackAvailable", CharacterState.bAttackAvailable);
	JsonObject->SetBoolField("bCanBeDamaged", CharacterState.bCanBeDamaged);
	JsonObject->SetBoolField("bFrameOver", CharacterState.bFrameOver);

	JsonObject->SetStringField("HitReaction", CharacterState.HitReaction);
	JsonObject->SetStringField("PrevState", CharacterState.PrevState);
	JsonObject->SetStringField("Direction", CharacterState.Direction);
	JsonObject->SetNumberField("TapInterval", CharacterState.TapInterval);

	// JSON을 FString으로 변환
	FString JsonString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	return JsonString;
}
