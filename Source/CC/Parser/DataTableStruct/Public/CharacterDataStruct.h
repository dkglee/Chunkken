#pragma once

#include "CoreMinimal.h"
#include "CharacterDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FCharacterDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WakeupSpeed;
};
