// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/GameInstance/Public/ChunkkenGameInstance.h"

#include "CharacterParser.h"
#include "ComboParser.h"
#include "ConditionListParser.h"
#include "InputParser.h"
#include "HitEffectParser.h"
#include "MoveParser.h"
#include "StateParser.h"
#include "TransitionParser.h"

UChunkkenGameInstance::UChunkkenGameInstance()
{
}

void UChunkkenGameInstance::Init()
{
	Super::Init();

	InputParser = NewObject<UInputParser>();
	InputParser->ParseData();

	HitEffectParser = NewObject<UHitEffectParser>();
	HitEffectParser->ParseData();

	StateParser = NewObject<UStateParser>();
	StateParser->ParseData();

	MoveParser = NewObject<UMoveParser>();
	MoveParser->ParserData();

	CharacterParser = NewObject<UCharacterParser>();
	CharacterParser->ParseData();

	ComboParser = NewObject<UComboParser>();
	ComboParser->ParseData();

	ConditionListParser = NewObject<UConditionListParser>();
	ConditionListParser->ParseData();

	TransitionParser = NewObject<UTransitionParser>();
	TransitionParser->ParseData();
}
