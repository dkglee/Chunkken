// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//평면제한
	GetCharacterMovement()->bConstrainToPlane=true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));
	
}

// Called when the game starts or when spawned
void AMyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacterBase::MoveRight);
	PlayerInputComponent->BindAction("Up", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Up", IE_Released, this, &ACharacter::StopJumping);

}

void AMyCharacterBase::MoveRight(float Value)
{
	if (FMath::Abs(Value)>KINDA_SMALL_NUMBER)
	{
		AddMovementInput(FVector(0.0f,1.0f,0.0f), Value);
	}
}

void AMyCharacterBase::Up(float Value)
{
}

