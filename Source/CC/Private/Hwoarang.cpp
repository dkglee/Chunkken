// Fill out your copyright notice in the Description page of Project Settings.


#include "Hwoarang.h"

#include "Components/BoxComponent.h"


// Sets default values
AHwoarang::AHwoarang()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Disabled;

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
void AHwoarang::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHwoarang::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
}

// Called every frame
void AHwoarang::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Display, TEXT("%d"), GetRemoteRole())
}

// Called to bind functionality to input
void AHwoarang::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHwoarang::Attack()
{
	CurrentState = EGameCharacterState::Attacking;
}

void AHwoarang::SetState(EGameCharacterState NewState)
{
	CurrentState = NewState;
}