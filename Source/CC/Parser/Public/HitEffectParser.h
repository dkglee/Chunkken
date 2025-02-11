#pragma once

#include <map>

#include "CoreMinimal.h"
#include "HitEffectStruct.h"
#include "UObject/Object.h"
#include "HitEffectParser.generated.h"

UCLASS()
class UHitEffectParser : public UObject
{
public:
	GENERATED_BODY()

	UHitEffectParser();

	UFUNCTION()
	void ParseData();

	static FHitEffectStruct GetHitEffect(int32 HitEffectID)
	{
		return HitEffectMap[HitEffectID];
	}

	static FHitEffectStruct GetHitEffectByMoveID(int32 MoveID)
	{
		return HitEffectByMoveIDMap[MoveID];
	}

protected:
	static std::map<int32, FHitEffectStruct> HitEffectMap;
	static std::map<int32, FHitEffectStruct> HitEffectByMoveIDMap;
};
