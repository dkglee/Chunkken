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
	static TArray<int32> GetGroupKeys()
	{
		TArray<int32> Keys;
		for (auto& [Key, Value] : StateMap)
		{
			// GroupID는 100단위로 구분되어 있다.
			if (Key % 100 != 0)
			{
				continue;
			}
			Keys.Add(Key);
		}
		return Keys;
	}
	static TArray<int32> GetStateKeys(int32 GroupID)
	{
		TArray<int32> Keys;
		for (auto& [Key, Value] : StateMap)
		{
			if (Value.ParentStateID == GroupID)
			{
				Keys.Add(Key);
			}
		}
		return Keys;
	}
	
	static int32 GetStateKey(const FString& StateName)
	{
		for (auto& [Key, Value] : StateMap)
		{
			if (Value.Name == StateName)
			{
				return Key;
			}
		}
		return -1;
	}

	static int32 GetParentStateKey(int32 StateID)
	{
		if (StateMap.find(StateID) == StateMap.end())
		{
			return -1;
		}
		return StateMap[StateID].ParentStateID;
	}
	
protected:
	std::vector<std::string> ParseCSVLine(const std::string& Line);
	std::string RestoreJson(const std::string& CsvJson);

	static std::map<int32, FStateDataStruct> StateMap;
};
