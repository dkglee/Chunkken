#include "TekkenFSM.h"

#include "AttackFSM.h"
#include "BaseCharacter.h"
#include "ConditionManager.h"
#include "CrouchingFSM.h"
#include "FastLogger.h"
#include "HitReactionFSM.h"
#include "IdleFSM.h"
#include "JumpFSM.h"
#include "MovementFSM.h"
#include "StateParser.h"
#include "TransitionParser.h"
#include "GameFramework/Character.h"
#include "GameFramework/MovementComponent.h"

UTekkenFSM::UTekkenFSM()
{
}

void UTekkenFSM::BeginPlay()
{
	Super::BeginPlay();

	Me = Cast<ABaseCharacter>(GetOwner());
	
	InitializeFSM();
	CurrentSubFSM = SubFSMs[UStateParser::GetStateKey(UIdleFSM::StateName)];
	CurrentSubFSM->Enter(-1);
}

void UTekkenFSM::ChangeSubFSM(int32 GroupID, int32 ChildID)
{
	PreviousSubFSM = CurrentSubFSM;
	
	// 이전 상태를 Wraping State에 저장.
	if (PreviousSubFSM)
	{
		FString PrevStateName = PreviousSubFSM->GetStateName();
		Me->CharacterState.PrevState = PrevStateName;
	}
	
	if (GroupID == -1) // 이미 Child가 부모 노드인 상황
	{
		CurrentSubFSM = SubFSMs[ChildID];
		PreviousSubFSM->Exit();
		CurrentSubFSM->Enter(-1);
	}
	else
	{
		CurrentSubFSM = SubFSMs[GroupID];
		PreviousSubFSM->Exit();
		CurrentSubFSM->Enter(ChildID);
	}

	// FFastLogger::LogConsole(TEXT("Change to %s"), *CurrentSubFSM->GetStateName());
}

void UTekkenFSM::Update(uint64 FrameIndex)
{
	// 대 그룹에서 다음의 것으로 넘어가는데 만약 그게 세부적인 ID라면?
	// 다음 FSM에 Enter를 호출할 때, 내 생각에는 어떤 세부 상태가 시작되어야 하는지를 같이 넘겨주면 된다.
	// first : GroupID, second : ChildID
	std::pair<int32, int32> Result;
	if (CheckTransitionList(Result))
	{
		ChangeSubFSM(Result.first, Result.second);
	}
	// SubFSM의 Update를 호출한다.
	CurrentSubFSM->Update();
}

void UTekkenFSM::InitializeFSM()
{
	SubFSMs.Add(UStateParser::GetStateKey(UIdleFSM::StateName), NewObject<UIdleFSM>(this, UIdleFSM::StaticClass()));
	SubFSMs.Add(UStateParser::GetStateKey(UMovementFSM::StateName), NewObject<UMovementFSM>(this, UMovementFSM::StaticClass()));
	SubFSMs.Add(UStateParser::GetStateKey(UCrouchingFSM::StateName), NewObject<UCrouchingFSM>(this, UCrouchingFSM::StaticClass()));
	SubFSMs.Add(UStateParser::GetStateKey(UJumpFSM::StateName), NewObject<UJumpFSM>(this, UJumpFSM::StaticClass()));
	SubFSMs.Add(UStateParser::GetStateKey(UAttackFSM::StateName), NewObject<UAttackFSM>(this, UAttackFSM::StaticClass()));
	SubFSMs.Add(UStateParser::GetStateKey(UHitReactionFSM::StateName), NewObject<UHitReactionFSM>(this, UHitReactionFSM::StaticClass()));

	for (auto& [Key, Value] : SubFSMs)
	{
		TransitionRules[Key].TransitionList = UTransitionParser::GetTransitionDataList(Key);
		Value->Initialize(Me, this);
	}
}

bool UTekkenFSM::CheckTransitionList(std::pair<int32, int32>& Result)
{
	FTransitionListDataStruct* HighestTransition = nullptr;
	
	// 여기서 모든 조건들을 검사하고 만약 조건이 맞는 것이 여러개라면 우선 순위에 따라서 실행한다.
	std::vector<FTransitionListDataStruct*> TransitionList = TransitionRules[UStateParser::GetStateKey(CurrentSubFSM->GetStateName())].TransitionList;
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

bool UTekkenFSM::ValidateCondition(FTransitionListDataStruct* Transition)
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

FString UTekkenFSM::WrapJsonString()
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

// 히트의 Reaction에는 세 가지 종류가 있다. (경직, 에어본, 넉다운)
// 3가지 상황을 감지하는 로직이 필요하다.
// 추가되어야 하는 조건이 뭘까?
// HitReaction이 올거다. 근데 어떤 HitReaction이 오는지에 대한 조건을 검사하면 된다.
// 1. Stun (경직) 조건이 추가 되어야 함
// 2. Airborne (에어본) 조건이 추가 되어야 함
// 3. Knockdown (넉다운) 조건이 추가 되어야 함.
// 이 이유는 해당 조건들은 데미지 컴퍼넌트가 조작을 하기 때문이다.!

// SubFSM에서 Group으로의 이동을 원하는 경우가 있다. 이 경우 어떻게 처리해야 할까?
// 이것은 이동하고자 하는 State의 ParentID가 없는 경우랑 동일하다고 볼 수 있다.
// 그렇다면 이는 Main FSM에게 이동을 요청하면 된다.

// 프레임이 필요한 부분은 State 내부에서 처리하자!
// 그럼 여기서 어떻게 하면 원하는 프레임 단위로 실행하도록 조건을 검사할 수 있을까?
// 그 조사는 그냥 직접하면 되는거 아닌가?
// 그래서 해당 프레임이 되면 알아서 true가 되게끔?
// 이렇게 하면 될 것 같은데?
// 