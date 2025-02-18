#pragma once

#include "CoreMinimal.h"
#include "ConditionStruct.generated.h"

USTRUCT(BlueprintType)
struct FConditionStruct
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 ConditionID;

	UPROPERTY()
	FString ConditionName;

	UPROPERTY()
	FString ConditionChecker;

	UPROPERTY()
	FString ConditionData; // JSON 형태로 저장

	UPROPERTY()
	FString ConditionGroup;
};
