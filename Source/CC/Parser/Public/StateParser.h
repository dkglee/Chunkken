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

	static FStateDataStruct GetState(int32 StateID)
	{
		return StateMap[StateID];
	}
	
protected:
	std::vector<std::string> ParseCSVLine(const std::string& Line);
	
	static std::map<int32, FStateDataStruct> StateMap;
};
