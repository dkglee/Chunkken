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
	int32 TransitionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 FromStateID;

	struct FLogicNode* ConditionLogic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 ToStateID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	int32 Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition Data")
	FString OnTransitionAction;
};
