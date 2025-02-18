#pragma once

#include "CoreMinimal.h"
#include "SubFSM.h"
#include "IdleFSM.generated.h"

UCLASS()
class UIdleFSM : public USubFSM
{
	GENERATED_BODY()
public:
	static FString StateName;

	virtual void Enter(int32 ChildID) override;
	virtual void Update() override;
	virtual void Exit() override;
	virtual FString GetStateName() override;
};
