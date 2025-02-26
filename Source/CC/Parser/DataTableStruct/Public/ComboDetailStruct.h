#pragma once

#include "CoreMinimal.h"
#include "ComboDetailStruct.generated.h"

USTRUCT(BlueprintType)
struct FComboDetailStruct
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int32 ComboID = -1;

	UPROPERTY()
	int32 StepOrder = -1;

	UPROPERTY()
	int32 MoveID = -1;

	UPROPERTY()
	bool bDashEvent = false;

	UPROPERTY()
	bool bTailSpinEvent = false;
};
