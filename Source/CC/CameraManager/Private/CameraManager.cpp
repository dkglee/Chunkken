// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"


#include "BaseCharacter.h"
#include "FastLogger.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACameraManager::ACameraManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Spring Arm 생성
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 1000.0f; // 기본 거리 설정
	SpringArm->bDoCollisionTest = false;

	// 카메라 생성 및 Spring Arm에 연결
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// 카메라 거리 및 속도 설정
	DefaultCameraDistance = 250.0f;
	ZoomSpeed = 5.0f;
	MaxCameraDistance = 1000.0f;
	MinCameraDistance = 250.0f;

	// 추적 상태
	bIsSpecialMode = false;
	bUseSpecialFocus = false;
}

void ACameraManager::RegisterPlayers(class ABaseCharacter* Left, class ABaseCharacter* Right)
{
	Player1 = Left;
	Player2 = Right;
	bRegistered = true;
}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();
}

void ACameraManager::UpdateCameraGameOver()
{
	if (!bGameDone) return ;
	
	if (bZoom)
	{
		// Closeup Camera
		float InterpFOV = FMath::FInterpTo(Camera->FieldOfView, 60.0f, GetWorld()->GetDeltaSeconds(), 3.0f);
		Camera->SetFieldOfView(InterpFOV);
		if (Camera->FieldOfView <= 61.0f && !DoOnce)
		{
			FFastLogger::LogScreen(FColor::Red, TEXT("Im Here"));
			DoOnce = true;
			FTimerHandle TimerHandle;
			TWeakObjectPtr<ACameraManager> WeakThis = this;

			bStopZoomDistance = true;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis]()
			{
				if (WeakThis.IsValid())
				{
					ACameraManager* StrongThis = WeakThis.Get();
					StrongThis->bZoom = false;
					StrongThis->bStopZoomDistance = false;
				}
			}), 1.0f, false);
		}
	}
	else
	{
		float InterpFOV = FMath::FInterpTo(Camera->FieldOfView, 90.0f, GetWorld()->GetDeltaSeconds(), 0.3f);
		Camera->SetFieldOfView(InterpFOV);
		if (Camera->FieldOfView >= 89.0f)
		{
			Camera->SetFieldOfView(90.0f);
			bGameDone = false;
		}
	}
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// FFastLogger::LogConsole(TEXT("Camera Tick: %p | %p | %p"), this, Player1, Player2);
	
	if (!bRegistered) return;

	
	UpdateCameraPosition();
	if (!bStopZoomDistance)
	{
		UpdateCameraZoom(DeltaTime);
	}
	// //특수모드일때 위치로 카메라 이동
	// else if (bIsSpecialMode && bUseSpecialFocus)
	// {
	// 	FVector CurrentLocation = GetActorLocation();
	// 	FVector NewLocation = FMath::VInterpTo(CurrentLocation, SpecialFocusPoint, DeltaTime, 5.0f);
	// 	SetActorLocation(NewLocation);
	// }
	UpdateCameraGameOver();
}
// 플레이어 중간 지점에 카메라 배치
void ACameraManager::UpdateCameraPosition()
{
	if (!Player1 || !Player2) return;

	FVector Player1Location = Player1->GetActorLocation();
	FVector Player2Location = Player2->GetActorLocation();

	// 두 플레이어의 중간 지점 계산
	FVector NewCameraLocation = (Player1Location + Player2Location) / 2;
	NewCameraLocation.Z += 20.0f;

	SetActorLocation(NewCameraLocation);
}

// 플레이어 거리 기반 줌 조정
void ACameraManager::UpdateCameraZoom(float DeltaTime)
{
	if (!Player1 || !Player2) return;

	float Distance = FVector::Dist(Player1->GetActorLocation(), Player2->GetActorLocation());

	// 카메라 거리 제한 (Min ~ Max 사이)
	float TargetDistance = FMath::Clamp(Distance, MinCameraDistance, MaxCameraDistance);

	// 부드러운 보간 (FInterpTo)
	float NewArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, TargetDistance, DeltaTime, ZoomSpeed);
	SpringArm->TargetArmLength = NewArmLength;
}



// 이벤트 위치를 전달받아 특수 효과를 트리거하는 함수
void ACameraManager::TriggerSpecialEffectAtLocation(const FVector& EventLocation)
{
	bIsSpecialMode = true;
	bUseSpecialFocus = true;
	SpecialFocusPoint = EventLocation;

	SpringArm->TargetArmLength = 100.0f;  

	TriggerStrongShake();

	GetWorldTimerManager().SetTimer(SpecialTimerHandle, this, &ACameraManager::EndSpecialEffect, 1.0f, false);
}

void ACameraManager::EndSpecialEffect()
{
	//원래 상태로 복귀
	bIsSpecialMode = false;
	bUseSpecialFocus = false;
	SpringArm->TargetArmLength = DefaultCameraDistance; 
	UE_LOG(LogTemp, Log, TEXT("Special effect ended, returning to normal tracking."));
}



void ACameraManager::TriggerWeakShake(float Scale)
{
	if (!WeakShakeClass)
	{
		UE_LOG(LogTemp, Error, TEXT("WeakShakeClass is not assigned!"));
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC && PC->PlayerCameraManager)
	{
		PC->PlayerCameraManager->StartCameraShake(WeakShakeClass, Scale);
		UE_LOG(LogTemp, Log, TEXT("TriggerWeakShake executed"));
	}
}

void ACameraManager::TriggerStrongShake()
{
	if (!StrongSequence) return;
	PlaySequenceShake(StrongSequence, 2.0f, 0.0f,3.0f);
	UE_LOG(LogTemp, Display, TEXT("strong"));
}

void ACameraManager::TriggerLandingShake()
{
	if (!LandingSequence) return;
	PlaySequenceShake(LandingSequence, 3.0f, 0.0f, 4.0f);
	UE_LOG(LogTemp, Display, TEXT("landing"));
}

void ACameraManager::PlaySequenceShake(ULevelSequence* Sequence, float Scale, float BlendInTime, float BlendOutTime)
{
	if (!SequenceCameraShakeClass) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC || !PC->PlayerCameraManager) return;


	PC->PlayerCameraManager->StartCameraShake(SequenceCameraShakeClass, Scale);
}