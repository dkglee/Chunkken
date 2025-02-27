#pragma once

#include "CoreMinimal.h"
#include "ConditionStruct.generated.h"

USTRUCT(BlueprintType)
struct FConditionStruct
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 ConditionID = -1;

	UPROPERTY()
	FString ConditionName = TEXT("");

	UPROPERTY()
	FString ConditionChecker = TEXT("");

	UPROPERTY()
	FString ConditionData = TEXT(""); // JSON 형태로 저장

	UPROPERTY()
	FString ConditionGroup = TEXT("");
};
