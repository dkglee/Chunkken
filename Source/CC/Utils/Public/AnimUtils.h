#pragma once

#include "CoreMinimal.h"
#include "AnimUtils.generated.h"

USTRUCT()
struct FAnimUtils
{
	GENERATED_BODY()

	static float CalculateAnimPlayRate(int32 TotalFrames, float Duration)
	{
		const float FPS = 60.0f;
		float TargetTime = TotalFrames / FPS; // 목표 출력 시간
		float PlayRate = Duration / TargetTime; // 원본 Duration 대비 목표 시간 비율
		return PlayRate;
	}
};
