// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"


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
	DefaultCameraDistance = 1200.0f;
	ZoomSpeed = 5.0f;
	MaxCameraDistance = 2000.0f;
	MinCameraDistance = 800.0f;
}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();

	// 모든 플레이어 찾기
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundPlayers);

	for (AActor* Players : FoundPlayers)
	{
		ACharacter* Player =Cast<ACharacter>(Players);
		if (Player->ActorHasTag(TEXT("Player1")))
		{
			Player1 = Player;
		}
		else if (Player->ActorHasTag(TEXT("Player2")))
		{
			Player2 = Player;
		}
	}
	
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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
