#pragma once

#include "CoreMinimal.h"
#include "AnimationDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FAnimationDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AnimID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AnimName;
};
