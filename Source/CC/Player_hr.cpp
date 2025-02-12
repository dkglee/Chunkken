// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_hr.h"


// Sets default values
APlayer_hr::APlayer_hr()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayer_hr::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer_hr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayer_hr::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayer_hr::MoveRight(float Value)
{
	Super::MoveRight(Value);
}

