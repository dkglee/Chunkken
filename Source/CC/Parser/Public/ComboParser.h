#pragma once

#include <map>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ComboDataStruct.h"
#include "ComboParser.generated.h"

UCLASS()
class UComboParser : public UObject
{
	GENERATED_BODY()
public:
	UComboParser();

	UFUNCTION()
	void ParseData();

protected:
	TArray<int32> ParseComboNotaion(int32 CharacterID, std::string LineToken);
	void ParseCombo();
	void ParseComboDetail();
	void PrintComboMap();

	static std::map<int32, FComboDataStruct> ComboMap;
};
