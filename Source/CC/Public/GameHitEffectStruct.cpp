#include "GameHitEffectStruct.h"

static TArray<FGameHitEffectStruct> HitEffectDatabase;

static void InitializeHitEffectDatabase()
{
	HitEffectDatabase.Add(FGameHitEffectStruct(1001, 10, "Normal"));
	HitEffectDatabase.Add(FGameHitEffectStruct(2001, 15, "Counter"));
}

	
FGameHitEffectStruct* FGameHitEffectStruct::GetHitEffectFromMoveID(int32 InMoveID)
{
	for (FGameHitEffectStruct& Effect : HitEffectDatabase)
	{
		if (Effect.MoveID == InMoveID)
		{
			return &Effect; 
		}
	}

	return nullptr;  
}
