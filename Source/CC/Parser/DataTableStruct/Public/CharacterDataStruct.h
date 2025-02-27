#pragma once

#include "CoreMinimal.h"
#include "CharacterDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FCharacterDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WakeupSpeed = 0;
};
