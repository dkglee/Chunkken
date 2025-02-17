#pragma once

#include "CoreMinimal.h"
#include "SubFSM.h"
#include "AttackFSM.generated.h"

UCLASS()
class UAttackFSM : public USubFSM
{
	GENERATED_BODY()
public:
	// TODO: static으로 해당 State의 이름을 선언하자.
	static FString StateName;

	virtual void Enter(int32 ChildID) override;
	virtual void Update() override;
	virtual void Exit() override;
	virtual FString GetStateName() override;
	virtual void ChangeState(int32 GroupID, int32 ChildID) override;
	virtual void Initialize(class ABaseCharacter* InMe, class UTekkenFSM* InOwnerFSM) override;
};
