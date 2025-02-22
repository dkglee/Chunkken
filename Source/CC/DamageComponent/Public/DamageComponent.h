// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CC_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDamageComponent();

	// Collision을 활성화 하는 것만 필요함 : 왜냐하면 BoxTrace로 검출이 가능하기 때문
	// 근데 나는 BoxTrace로 검출할거임 ㅇㅇ
	bool DetectCollision(const FString& SocketName);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	class ABaseCharacter* Me;

	UPROPERTY()
	float SphereRadius = 50.0f;

	UPROPERTY()
	int32 HP = 100.0f;
};
