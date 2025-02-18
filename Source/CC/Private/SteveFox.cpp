// Fill out your copyright notice in the Description page of Project Settings.


#include "SteveFox.h"

#include "Components/BoxComponent.h"

// Sets default values
ASteveFox::ASteveFox()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 체력 기본 값 설정
	HP = 100;

	// 히트박스 설정
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);

	// 허트박스 설정
	HurtBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HurtBox"));
	HurtBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASteveFox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASteveFox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASteveFox::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASteveFox::Attack()
{
	CurrentState = EGameCharacterState::Attacking;
}

void ASteveFox::SetState(EGameCharacterState NewState)
{
	CurrentState = NewState;
}