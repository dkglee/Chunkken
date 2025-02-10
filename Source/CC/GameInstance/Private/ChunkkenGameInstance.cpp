// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/GameInstance/Public/ChunkkenGameInstance.h"

#include "InputParser.h"
#include "CC.h"

UChunkkenGameInstance::UChunkkenGameInstance()
{
}

void UChunkkenGameInstance::Init()
{
	Super::Init();

	InputParser = NewObject<UInputParser>();
	InputParser->ParseInput();

}
