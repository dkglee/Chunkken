#pragma once

#include <map>

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "TekkenAnimIntance.h"
#include "UObject/Object.h"
#include "TransitionRules.h"
#include "SubFSM.generated.h"

// 외부에서 외부로 이동하는 것은 MainFSM이 처리하고, 내부에서 내부로 이동하는 것은 SubFSM이 처리한다.
UCLASS()
class USubFSM : public UObject
{
	GENERATED_BODY()
public:
	USubFSM() {}

	virtual void Initialize(class ABaseCharacter* InMe, class UTekkenFSM* InOwnerFSM);
	virtual void Enter(int32 ChildID);
	virtual void Update();
	virtual void Exit();
	virtual void ChangeState(int32 GroupId, int32 ChildId);
	virtual FString GetStateName() { return TEXT(""); }
	class UBaseState* GetCurrentState();

protected:
	virtual bool CheckTransitionList(std::pair<int32, int32>& Result);
	virtual bool ValidateCondition(FTransitionListDataStruct* Transition);
	FString WrapJsonString();

	UPROPERTY()
	class ABaseCharacter* Me = nullptr;
	UPROPERTY()
	class UTekkenFSM* OwnerFSM = nullptr;
	UPROPERTY()
	class UTekkenAnimIntance* TekkenAnimInstance = nullptr;
	UPROPERTY()
	class UBaseState* CurrentState = nullptr;
	UPROPERTY()
	class UTekkenCameraShakeManager* CameraManager = nullptr;
	std::map<int32, FTransitionRules> TransitionRules;
	UPROPERTY()
	TMap<int32, class UBaseState*> States;
};
