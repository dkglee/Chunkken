#include "GameHitEffectStruct.h"

namespace GameHitEffect  
{
	static TArray<FGameHitEffectStruct> HitEffectDatabase;
		static void InitializeHitEffectDatabase()
	{
		HitEffectDatabase.Add(FGameHitEffectStruct(1001, 10, "Normal"));
		HitEffectDatabase.Add(FGameHitEffectStruct(2001, 15, "Counter"));
	}

	
	FGameHitEffectStruct* GetHitEffectFromMoveID(int32 MoveID)
	{
		for (FGameHitEffectStruct& Effect : HitEffectDatabase)
		{
			if (Effect.MoveID == MoveID)
			{
				return &Effect; 
			}
		}

		return nullptr;  
	}
}
