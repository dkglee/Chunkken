// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"

#include "BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// SphereTrace를 활성화 하는 함수
bool UDamageComponent::DetectCollision(const FString& SocketName)
{
	FVector Start = Me->GetMesh()->GetSocketLocation(*SocketName);
	
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(Me);
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, Start, SphereRadius, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResult, true);

	if (!HitResult.bBlockingHit)
	{
		return false;
	}

	// 충돌 감지! 연속 충돌 감지 제거 필요
	ABaseCharacter* Target = Cast<ABaseCharacter>(HitResult.GetActor());
	if (!Target)
	{
		return false;
	}

	// 데미지 계산
	// 여기서 데미지를 입히는 과정들은 넣어야 겠다! ㅇㅇ
	// Damage 업데이트
	
	return true;
}
