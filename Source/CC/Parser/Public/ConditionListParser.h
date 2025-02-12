#pragma once

#include <map>

#include "CoreMinimal.h"
#include "ConditionStruct.h"
#include "UObject/Object.h"
#include "ConditionListParser.generated.h"

UCLASS()
class UConditionListParser : public UObject
{
	GENERATED_BODY()
public:
	UConditionListParser();

	UFUNCTION()
	void ParseData();

	static const FConditionStruct* GetConditionData(int32 ConditionID);
	
protected:
	std::vector<std::string> ParseCSVLine(const std::string& Line);
	std::string RestoreJson(const std::string& CsvJson);

	static std::map<int32, FConditionStruct> ConditionMap;
};
