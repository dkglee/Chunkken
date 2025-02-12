#pragma once

#include "CoreMinimal.h"
#include "TransitionListDataStruct.generated.h"

UENUM(BlueprintType)
enum class EConditionLogic : uint8
{
	NONE UMETA(DisplayName = "None"),
	AND  UMETA(DisplayName = "AND"),
	OR   UMETA(DisplayName = "OR"),
	NOT  UMETA(DisplayName = "NOT")
};

USTRUCT(BlueprintType)
struct FTransitionListDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 TransitionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 FromStateID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	bool bParentStateCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	EConditionLogic ConditionLogic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	TArray<int32> ConditionIDs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 ToStateID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	FString OnTransitionAction;
};
