// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacterBase.h"
#include "Player_hr.generated.h"

UCLASS()
class CC_API APlayer_hr : public AMyCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_hr();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void MoveRight(float Value);

};
