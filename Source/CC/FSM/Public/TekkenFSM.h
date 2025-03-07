// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>
#include <utility>

#include "CoreMinimal.h"
#include "TransitionListDataStruct.h"
#include "Components/ActorComponent.h"
#include "TransitionRules.h"
#include "TekkenFSM.generated.h"

UCLASS()
class CC_API UTekkenFSM : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTekkenFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void ChangeSubFSM(int32 GroupID, int32 ChildID);
	// Called every frame
	void Update(uint64 FrameIndex);
	UFUNCTION()
	class UBaseState* GetCurrentState();
	class USubFSM* GetCurrentFSM();

protected:
	void InitializeFSM();
	bool CheckTransitionList(std::pair<int32, int32>& result);
	bool ValidateCondition(FTransitionListDataStruct* LogicNode);
	FString WrapJsonString();
	
	UPROPERTY()
	class USubFSM* PreviousSubFSM = nullptr;
	UPROPERTY()
	class USubFSM* CurrentSubFSM = nullptr;

	// 초기화 해야 하는것!
	std::map<int32, FTransitionRules> TransitionRules;
	UPROPERTY()
	TMap<int32, class USubFSM*> SubFSMs;

	UPROPERTY()
	class ABaseCharacter* Me = nullptr;
};
