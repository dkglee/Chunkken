#pragma once

#include "CoreMinimal.h"
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

protected:
	
};
