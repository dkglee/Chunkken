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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual bool IsLeftPlayer(){return false;};
	
	UFUNCTION()
	class UBaseState* GetCurrentState();
	UFUNCTION()
	class USubFSM* GetSubFSM();
	UFUNCTION()
	class UDamageComponent* GetDamageComponent();
	UFUNCTION()
	void ClearMoveSetForce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void UpdateMovement(uint64 FrameIndex, const FExecutingMove& ExecutingMove);
	virtual void UpdateAttack(uint64 FrameIndex, const FExecutingMove& ExecutingMove);
	void ClearMoveset();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	FCharacterState CharacterState;

	UPROPERTY(EditDefaultsOnly, Category="Anim")
	TSubclassOf<class UTekkenAnimIntance> TekkenAnimClass;
	// 충돌 및 데미지 처리 컴포넌트

	
	FExecutingMove CurrentExecutingMove;
	bool bResetMoveSet = false;
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UInputManager* InputManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UTekkenFSM* TekkenFSM;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UDamageComponent* DamageComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	int32 CharID;

	// 이건 나중에 InputComponent로 빠져도 될 것 같음
	TArray<FExecutingMove> Moveset;
	int32 MoveIndex = 0;
};
