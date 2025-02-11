#pragma once

#include "CoreMinimal.h"
#include "ComboDetailStruct.generated.h"

USTRUCT(BlueprintType)
struct FComboDetailStruct
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int32 ComboID;

	UPROPERTY()
	int32 StepOrder;

	UPROPERTY()
	int32 MoveID;

	UPROPERTY()
	bool bDashEvent;

	UPROPERTY()
	bool bTailSpinEvent;
};
