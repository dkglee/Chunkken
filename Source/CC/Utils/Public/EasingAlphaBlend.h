#pragma once

#include "CoreMinimal.h"
#include "FastLogger.h"
#include "EasingAlphaBlend.generated.h"

USTRUCT()
struct FEasingAlphaBlend
{
	GENERATED_BODY()
public:
	static float EasingAlphaBlend(float Start, float End, float Delta, float InterpSpeed, bool& bEnd)
	{
		if (InterpSpeed <= 0.0f)
		{
			bEnd = true;
			return End;
		}

		const float Dist = End - Start;
    
		if (FMath::Square(Dist) < SMALL_NUMBER)
		{
			bEnd = true;
			return End;
		}

		const float DeltaMove = Dist * FMath::Clamp<float>(Delta * InterpSpeed, 0.0f, 1.0f);
    
		return Start + DeltaMove;
	}

	static FVector EasingVectorBlend(FVector Start, FVector End, float Delta, float InterpSpeed, bool& bEnd)
	{
		bool Temp;
		FVector EasedValue = FVector(
			EasingAlphaBlend(Start.X, End.X, Delta, InterpSpeed, Temp),
			EasingAlphaBlend(Start.Y, End.Y, Delta, InterpSpeed, Temp),
			EasingAlphaBlend(Start.Z, End.Z, Delta, InterpSpeed, bEnd)
		);
		return EasedValue;
	}
};
