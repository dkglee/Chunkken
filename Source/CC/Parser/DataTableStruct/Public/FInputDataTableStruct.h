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
	int32 InputID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bitmask")
	int32 BitIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bitmask")
	int32 BitMaskDec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bitmask")
	FString BitMaskHex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bitmask")
	FString BitMaskBin;
};