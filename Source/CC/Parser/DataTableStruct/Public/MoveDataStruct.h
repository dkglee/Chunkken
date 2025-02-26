#pragma once

#include "CoreMinimal.h"
#include "MoveDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FMoveDataStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MoveID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharID = -1;

	UPROPERTY(EditAnywhere)
	uint64 Command = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RelativeID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AttackType = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hits = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HitLevel = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartUp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ActiveFrames = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Recovery = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OnBlock = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OnHit = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AnimID = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SocketID = -1;
};
