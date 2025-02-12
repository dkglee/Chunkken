#pragma once

#include <map>

#include "CoreMinimal.h"
#include "TransitionListDataStruct.h"
#include "UObject/Object.h"
#include "TransitionParser.generated.h"

UCLASS()
class UTransitionParser : public UObject
{
	GENERATED_BODY()
public:
	UTransitionParser();

	UFUNCTION()
	void ParseData();

	static const FTransitionListDataStruct* GetTransitionData(int32 TransitionID);
	
protected:
	EConditionLogic ParserConditionLogic(std::string LineToken);
	TArray<int32> ParserConditionIDs(std::string LineToken);
	void PrintTransitionMap();

	static std::map<int32, FTransitionListDataStruct> TransitionMap;
};
