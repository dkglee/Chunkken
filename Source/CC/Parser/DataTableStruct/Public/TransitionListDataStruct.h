#pragma once

#include "CoreMinimal.h"
#include "TransitionListDataStruct.generated.h"

struct FLogicNode
{
	FString Value;
	struct FLogicNode* Left;
	struct FLogicNode* Right;

	FLogicNode()
		: Value(""), Left(nullptr), Right(nullptr)
	{
	}
	
	FLogicNode(FString InValue, struct FLogicNode* InLeft = nullptr, struct FLogicNode* InRight = nullptr)
		: Value(InValue), Left(InLeft), Right(InRight)
	{
	}

	// AST 평가 함수
	bool Evaluate(const TMap<FString, bool>& Values)
	{
		if (Value == "&")
		{
			return Left->Evaluate(Values) && Right->Evaluate(Values);
		}
		else if (Value == "|")
		{
			return Left->Evaluate(Values) || Right->Evaluate(Values);
		}
		else if (Value == "!")
		{
			return !Left->Evaluate(Values);
		}
		else
		{
			return Values.Contains(Value) ? Values[Value] : false;
		}
	}
};

USTRUCT(BlueprintType)
struct FTransitionListDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 TransitionID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 FromStateID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	TArray<FString> ConditionTokens;
	
	struct FLogicNode* ConditionLogic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 ToStateID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 Priority = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	FString OnTransitionAction = TEXT("");
};
