// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "Hwoarang.h"
#include "SteveFox.h"


// Sets default values
AGameManager::AGameManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	// 플레이어 찾기
	for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
	{
		ACharacter* Player = *It;

		if (Player->IsA(AHwoarang::StaticClass()))
		{
			Player1 = Cast<AHwoarang>(Player);
		}
		else if (Player->IsA(ASteveFox::StaticClass()))
		{
			Player2 = Cast<ASteveFox>(Player);
		}
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AGameManager::HandleAttack(ACharacter* Attacker, int32 MoveID)
{
	if (!Player1 || !Player2)
	{
		UE_LOG(LogTemp, Error, TEXT("Players not found!"));
		return;
	}

	ACharacter* Defender = (Attacker == Player1) ? Player2 : Player1;

	bool bHit = ACollision::CheckCollision(Cast<AFightingCharacter>(Attacker), Cast<AFightingCharacter>(Defender));

	if (bHit)
	{
		UDamageComponent::ApplyDamage(Cast<AFightingCharacter>(Attacker), Cast<AFightingCharacter>(Defender), MoveID);
	}
}