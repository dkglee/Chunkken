#pragma once

#include <map>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AnimationDataStruct.h"
#include "AnimParser.generated.h"

UCLASS()
class UAnimParser : public UObject
{
	GENERATED_BODY()
public:
	UAnimParser();

	UFUNCTION()
	void ParseData();

	static const FAnimationDataStruct* GetAnimData(int32 AnimID);

protected:
	static std::map<int32, FAnimationDataStruct> AnimationDataMap;
};
