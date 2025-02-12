#pragma once

#include "CoreMinimal.h"
#include "StateDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FStateDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StateID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ParentStateID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StateGroup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefaultDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AnimationRef;

};
