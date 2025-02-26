// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CameraManager.generated.h"


class USpringArmComponent;
class UCameraComponent;
class ULevelSequence;
class UCameraShakeBase;
class ULevelSequence;


UCLASS()
class CC_API ACameraManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACameraManager();

	void RegisterPlayers(class ABaseCharacter* Left, class ABaseCharacter* Right);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UpdateCameraGameOver();
	void Tick(float DeltaTime);

public:
	// 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	// 플레이어 참조
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABaseCharacter* Player1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABaseCharacter* Player2;
	bool bRegistered = false;
	bool DoOnce = false;
	bool bZoom = true;
	bool bStopZoomDistance = false;

	//카메라 테스트
	FTimerHandle WeakShakeTimerHandle;

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

	//카메라 쉐이크
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	TSubclassOf<UCameraShakeBase> WeakShakeClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	TSubclassOf<class UCameraShakeBase> SequenceCameraShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraShake")
	ULevelSequence* WeakSequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraShake")
	ULevelSequence* StrongSequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraShake")
	ULevelSequence* LandingSequence;

	// 약한 흔들림
	UFUNCTION(BlueprintCallable, Category = "CameraShake")
	void TriggerWeakShake();

	// 강한 흔들림
	UFUNCTION(BlueprintCallable, Category = "CameraShake")
	void TriggerStrongShake();

	// 캐릭터 착지 시 흔들림
	UFUNCTION(BlueprintCallable, Category = "CameraShake")
	void TriggerLandingShake();

	void SetGameDone(bool bDone) { bGameDone = bDone; }
private:
	void PlaySequenceShake(ULevelSequence* Sequence, float Scale, float BlendInTime, float BlendOutTime);

	bool bGameDone = false;
};
