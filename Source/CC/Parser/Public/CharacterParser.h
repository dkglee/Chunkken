#pragma once

#include <map>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharacterDataStruct.h"
#include "CharacterParser.generated.h"

UCLASS()
class UCharacterParser : public UObject
{
	GENERATED_BODY()
public:
	UCharacterParser();

	UFUNCTION()
	void ParseData();

	static const FCharacterDataStruct* GetCharacterData(int32 CharID);

protected:
	static std::map<int32, FCharacterDataStruct> CharacterDataMap;
};
