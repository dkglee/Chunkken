// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"


#include "BaseCharacter.h"
#include "FastLogger.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ACameraManager::ACameraManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Spring Arm 생성
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 1200.0f; // 기본 거리 설정
	SpringArm->bDoCollisionTest = false;

	// 카메라 생성 및 Spring Arm에 연결
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// 카메라 거리 및 속도 설정
	DefaultCameraDistance = 500.0f;
	ZoomSpeed = 5.0f;
	MaxCameraDistance = 1000.0f;
	MinCameraDistance = 400.0f;
}

void ACameraManager::RegisterPlayers(class ABaseCharacter* Left, class ABaseCharacter* Right)
{
	Player1 = Left;
	Player2 = Right;
}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// FFastLogger::LogScreen(FColor::Cyan, TEXT("Tick %d %d"), Player1 ? 1 : 0, Player2 ? 1 : 0);
	if (Player1 && Player2)
	{
		UpdateCameraPosition();
		UpdateCameraZoom(DeltaTime);
	}
}
// 플레이어 중간 지점에 카메라 배치
void ACameraManager::UpdateCameraPosition()
{
	if (!Player1 || !Player2) return;

	FVector Player1Location = Player1->GetActorLocation();
	FVector Player2Location = Player2->GetActorLocation();

	// 두 플레이어의 중간 지점 계산
	FVector NewCameraLocation = (Player1Location + Player2Location) / 2;
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
