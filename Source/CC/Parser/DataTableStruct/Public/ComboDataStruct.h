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
	int32 ComboID;

	UPROPERTY()
	int32 CharID;

	UPROPERTY()
	FString ComboName;

	UPROPERTY()
	TArray<int32> Notation;
	
	UPROPERTY()
	TArray<FComboDetailStruct> ComboDetails;

	UPROPERTY()
	int32 EstimatedDamage;
};
