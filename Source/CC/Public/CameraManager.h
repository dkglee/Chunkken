// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CameraManager.generated.h"

UCLASS()
class CC_API ACameraManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACameraManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);

public:
	// 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	// 플레이어 참조
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACharacter* Player1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACharacter* Player2;

	// 카메라 위치 조정
	void UpdateCameraPosition();

	// 카메라 줌 조정
	void UpdateCameraZoom(float DeltaTime);

	// 카메라 기본 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultCameraDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZoomSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCameraDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinCameraDistance;
	
};
