#pragma once

#include <map>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StateDataStruct.h"
#include "StateParser.generated.h"

UCLASS()
class UStateParser : public UObject
{
	GENERATED_BODY()
public:
	UStateParser();

	UFUNCTION()
	void ParseData();

	static const FStateDataStruct* GetState(int32 StateID)
	{
		if (StateMap.find(StateID) == StateMap.end())
		{
			return nullptr;
		}
		return &StateMap[StateID];
	}
	
protected:
	std::vector<std::string> ParseCSVLine(const std::string& Line);
	std::string RestoreJson(const std::string& CsvJson);

	static std::map<int32, FStateDataStruct> StateMap;
};
