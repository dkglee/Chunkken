#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MovesParser.generated.h"

#define MAX_INPUT_BUFFER 10

// UENUM(BlueprintType)
// enum class EInputMask : uint8
// {
// 	None    = 0,
// 	Up      = 1 << 0,  // 00000001
// 	Down    = 1 << 1,  // 00000010
// 	Left    = 1 << 2,  // 00000100d
// 	Right   = 1 << 3,  // 00001000
// 	LP      = 1 << 4,  // 00010000 (왼손 펀치)
// 	RP      = 1 << 5,  // 00100000 (오른손 펀치)
// 	LK      = 1 << 6,  // 01000000 (왼발 킥)
// 	RK      = 1 << 7   // 10000000 (오른발 킥)
// };

// USTRUCT(BlueprintType)
// struct FInputData : public FTableRowBase
// {
// 	GENERATED_BODY()
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	uint8 InputMask;
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	float TimeStamp;
// };

// USTRUCT(BlueprintType)
// struct FMoveData : public FTableRowBase
// {
// 	GENERATED_BODY()

// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	int32 MoveID;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	FString MoveName;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	TArray<uint8> CommandSequence;
// };

UCLASS()
class UMovesParser : public UObject
{
	GENERATED_BODY()

private:
	// static TArray<uint8> InputBuffer;
	//
	// static int32 MaxBufferSize;

public:
	// UFUNCTION(BlueprintCallable, Category = "Move Parsing")
	// static void AddInput(uint8 NewInput);
	//
	// UFUNCTION(BlueprintCallable, Category = "Move Parsing")
	// static FMoveData ParseInputBuffer(UDataTable* MoveTable);

};
