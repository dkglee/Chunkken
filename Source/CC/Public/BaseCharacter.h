// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "CharacterState.h"
#include "ExecutingMove.h"
#include "GameCharacterState.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()class CC_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual void OnPressedInput(int32 InputID, uint64 FrameIndex, bool bLeft);
	virtual void OnReleasedInput(int32 InputID, uint64 FrameIndex, bool bLeft);
	virtual void Update(uint64 FrameIndex);
	UFUNCTION()
	class UBaseState* GetCurrentState();
	UFUNCTION()
	class USubFSM* GetSubFSM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void UpdateMovement(uint64 FrameIndex, const FExecutingMove& ExecutingMove);
	virtual void UpdateAttack(uint64 FrameIndex, const FExecutingMove& ExecutingMove);
	void ClearMoveset();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	FCharacterState CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	class UBoxComponent* HitBox; //공격판정

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	class UBoxComponent* HurtBox; //피격판정

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="State")
	EGameCharacterState CurrentState;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void Attack();

	UFUNCTION(BlueprintCallable, Category="State")
	void SetState(EGameCharacterState NewState);

	UPROPERTY(EditDefaultsOnly, Category="Anim")
	TSubclassOf<class UTekkenAnimIntance> TekkenAnimClass;
	
	FExecutingMove CurrentExecutingMove;
	
	bool bResetMoveSet = false;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	class UInputManager* InputManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	class UTekkenFSM* TekkenFSM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	int32 CharID;

	TArray<FExecutingMove> Moveset;
	int32 MoveIndex = 0;
};
