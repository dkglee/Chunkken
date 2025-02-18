// Fill out your copyright notice in the Description page of Project Settings.


#include "CC/Public/Collision.h"

#include "Hwoarang.h"
#include "SteveFox.h"
#include "Components/BoxComponent.h"


// Sets default values
ACollision::ACollision()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACollision::CheckCollision(ACharacter* Attacker, ACharacter* Defender)
{
	if (!Attacker || !Defender)
	{
		return false;
	}

	UBoxComponent* AttackerHitBox = Cast<UBoxComponent>(Attacker->FindComponentByClass<UBoxComponent>());
	UBoxComponent* DefenderHurtBox = Cast<UBoxComponent>(Defender->FindComponentByClass<UBoxComponent>());

	if (!AttackerHitBox || !DefenderHurtBox)
	{
		return false;
	}

	// 박스 중심과 크기를 가져와서 충돌 감지. 히트박스와 허트박스가 겹치는지 확인
	FVector AttackerLocation = AttackerHitBox->GetComponentLocation();
	FVector AttackerExtent = AttackerHitBox->GetScaledBoxExtent();

	FVector DefenderLocation = DefenderHurtBox->GetComponentLocation();
	FVector DefenderExtent = DefenderHurtBox->GetScaledBoxExtent();

	// 두 박스가 충돌하는지 확인 (AABB 충돌 감지)
	bool bXCollision = FMath::Abs(AttackerLocation.X - DefenderLocation.X) <= (AttackerExtent.X + DefenderExtent.X);
	bool bYCollision = FMath::Abs(AttackerLocation.Y - DefenderLocation.Y) <= (AttackerExtent.Y + DefenderExtent.Y);
	bool bZCollision = FMath::Abs(AttackerLocation.Z - DefenderLocation.Z) <= (AttackerExtent.Z + DefenderExtent.Z);

	return bXCollision && bYCollision && bZCollision;
}