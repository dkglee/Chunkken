#pragma once

#include "CoreMinimal.h"
#include "SubFSM.h"
#include "MovementFSM.generated.h"

UCLASS()
class UMovementFSM : public USubFSM
{
	GENERATED_BODY()
public:
	static FString StateName;

	virtual void Enter(int32 ChildID) override;
	virtual void Update() override;
	virtual void Exit() override;
	virtual FString GetStateName() override;
	virtual void ChangeState(int32 GroupID, int32 ChildID) override;
	virtual void Initialize(class ABaseCharacter* InMe, class UTekkenFSM* InOwnerFSM) override;
};
