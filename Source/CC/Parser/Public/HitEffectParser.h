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

	static const FHitEffectStruct* GetHitEffect(int32 HitEffectID)
	{
		if (HitEffectMap.find(HitEffectID) == HitEffectMap.end())
		{
			return nullptr;
		}
		return &HitEffectMap[HitEffectID];
	}

	static int32 GetHitEffectByMoveID(int32 MoveID)
	{
		return HitEffetIDMap[MoveID];
	}

protected:
	static std::map<int32, FHitEffectStruct> HitEffectMap;
	static std::map<int32, int32> HitEffetIDMap;
};
