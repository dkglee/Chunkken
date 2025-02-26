// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FInputDataTableStruct.generated.h"

USTRUCT(BlueprintType)
struct FInputDataTableStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	int32 InputID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	FString Name = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bitmask")
	int32 BitIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bitmask")
	int32 BitMaskDec = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bitmask")
	FString BitMaskHex = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bitmask")
	FString BitMaskBin = TEXT("");
};