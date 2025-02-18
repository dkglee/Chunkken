#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HitEffectStruct.generated.h"

USTRUCT(BlueprintType)
struct FHitEffectStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HitEffectID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MoveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Condition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ExtraDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Launch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StunFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HitReaction;
};
