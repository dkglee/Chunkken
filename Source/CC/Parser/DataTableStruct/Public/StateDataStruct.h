#pragma once

#include "CoreMinimal.h"
#include "StateDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FStateDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StateID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = TEXT("");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ParentStateID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StateGroup = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefaultDuration = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AnimationRef = TEXT("");
};
