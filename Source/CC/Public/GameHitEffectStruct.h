#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameHitEffectStruct.generated.h"


USTRUCT(BlueprintType)
struct FGameHitEffectStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HitEffect")
	int32 MoveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HitEffect")
	int32 ExtraDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HitEffect")
	FString HitReaction;

	FGameHitEffectStruct()
		: MoveID(0), ExtraDamage(0), HitReaction(TEXT("")) {}

	FGameHitEffectStruct(int32 InMoveID, int32 InExtraDamage, FString InHitReaction)
		: MoveID(InMoveID), ExtraDamage(InExtraDamage), HitReaction(InHitReaction) {}

	FGameHitEffectStruct* GetHitEffectFromMoveID(int32 InMoveID);
};

