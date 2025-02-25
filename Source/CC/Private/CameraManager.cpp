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
	SpringArm->TargetArmLength = 250.0f; // 기본 거리 설정
	SpringArm->bDoCollisionTest = false;

	// 카메라 생성 및 Spring Arm에 연결
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// 카메라 거리 및 속도 설정
	DefaultCameraDistance = 250.0f;
	ZoomSpeed = 5.0f;
	MaxCameraDistance = 400.0f;
	MinCameraDistance = 250.0f;

	//static ConstructorHelpers::FObjectFinder<ACameraManager>
	MinCameraDistance = 220.0f;
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
	GetWorldTimerManager().SetTimer(WeakShakeTimerHandle, this, &ACameraManager::TriggerWeakShake, 5.0f, true, 3.0f);
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

void ACameraManager::TriggerWeakShake()
{
	if (!WeakShakeClass)
	{
		UE_LOG(LogTemp, Error, TEXT("WeakShakeClass is not assigned!"));
		return;
	}


	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC && PC->PlayerCameraManager)
	{

		PC->PlayerCameraManager->StartCameraShake(WeakShakeClass, 1.0f);
		UE_LOG(LogTemp, Log, TEXT("TriggerWeakShake executed"));
	}
}

void ACameraManager::TriggerStrongShake()
{
	if (!StrongSequence) return;
	PlaySequenceShake(StrongSequence, 2.0f, 1.0f,3.0f);
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