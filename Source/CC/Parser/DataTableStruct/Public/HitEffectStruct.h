#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HitEffectStruct.generated.h"

USTRUCT(BlueprintType)
struct FHitEffectStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HitEffectID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MoveID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Condition = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ExtraDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Launch = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StunFrames = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HitReaction = TEXT("");
};
