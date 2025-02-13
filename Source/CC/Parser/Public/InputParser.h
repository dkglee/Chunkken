#pragma once

#include <map>
#include <unordered_map>

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "InputParser.generated.h"

UCLASS()
class UInputParser : public UObject
{
	GENERATED_BODY()
public:
	UInputParser();
	
	UFUNCTION()
	void ParseData();

	static unsigned char GetBitmask(int32 Index)
	{
		return InputMap[Index];
	}

	static int32 GetIndex(const std::string& Name)
	{
		return InputNameMap[Name];
	}

protected:
	static std::map<int32, unsigned char> InputMap;
	static std::unordered_map<std::string, int32> InputNameMap;
};
