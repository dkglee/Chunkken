#pragma once

#include "CoreMinimal.h"
#include "GameCharacterState.generated.h"

UENUM(BlueprintType)
enum class EGameCharacterState : uint8
{
	Idle        UMETA(DisplayName = "Idle"),
	Attacking   UMETA(DisplayName = "Attacking"),
	Hit         UMETA(DisplayName = "Hit")
};
