// Fill out your copyright notice in the Description page of Project Settings.


#include "SteveFox.h"

#include "Components/BoxComponent.h"

// Sets default values
ASteveFox::ASteveFox()
{
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	
	CharID = 101;

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
void ASteveFox::Attack()
{
	CurrentState = EGameCharacterState::Attacking;
}

void ASteveFox::SetState(EGameCharacterState NewState)
{
	CurrentState = NewState;
}