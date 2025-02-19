#pragma once

#include "CoreMinimal.h"
#include "EasingAlphaBlend.generated.h"

USTRUCT()
struct FEasingAlphaBlend
{
	GENERATED_BODY()
public:
	static float EasingAlphaBlend(float DeltaTime, float Duration)
	{
		// Normalize time (0 ~ 1)
		float Alpha = FMath::Clamp(DeltaTime / Duration, 0.0f, 1.0f);

		// Apply ease-in-out using a sinusoidal curve
		float EasedValue = 0.5f * (1.0f - FMath::Cos(Alpha * PI)); 

		return EasedValue; // 0 ~ 1 사이 값 반환
	}
};
