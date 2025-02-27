#pragma once

#include "CoreMinimal.h"
#include "ComboDetailStruct.h"
#include "ComboDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FComboDataStruct
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int32 ComboID = -1;

	UPROPERTY()
	int32 CharID = -1;

	UPROPERTY()
	FString ComboName = TEXT("");

	UPROPERTY()
	TArray<int32> Notation;
	
	UPROPERTY()
	TArray<FComboDetailStruct> ComboDetails;

	UPROPERTY()
	int32 EstimatedDamage = 0;
};
