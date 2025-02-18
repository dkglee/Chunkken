// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

#include "CameraManager.h"
#include "FastLogger.h"
#include "MyPlayerController.h"
#include "Hwoarang.h"
#include "SteveFox.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"


AMyGameMode::AMyGameMode()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();

	DefaultPawnClass = nullptr;
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	//플레이어1,2 스폰
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FVector Player1Location(0,-200,0);
	FRotator Player1Rotation({0, 90, 0});
	ABaseCharacter* Player1 = GetWorld()->SpawnActor<ABaseCharacter>(HwoarangClass, Player1Location, Player1Rotation);
	if(Player1)
	{
		Player1->Tags.Add(FName("Player1")); // 태그 추가 (수정된 부분)
	}
	
	FVector Player2Location(0,200,0);
	FRotator Player2Rotation({0, -90, 0});
	ABaseCharacter* Player2 = GetWorld()->SpawnActor<ABaseCharacter>(SteveFoxClass, Player2Location, Player2Rotation);
	if(Player2)
	{
		Player2->Tags.Add(FName("Player2")); // 태그 추가 (수정된 부분)
	}
	
	//카메라 스폰
	FVector CameraLocation(0,0,90);
	FRotator CameraRotation(0,0,0);
	ACameraManager* CameraManager = GetWorld()->SpawnActor<ACameraManager>(ACameraManager::StaticClass(), CameraLocation, CameraRotation);
	
	//카메라 뷰포트 설정
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC && CameraManager)
	{
		FFastLogger::LogScreen(FColor::Red, TEXT("Camera Manager"));
		// PC->SetViewTarget(CameraManager);
		CameraManager->RegisterPlayers(Player1, Player2);
		PC->Possess(CameraManager);
	}
	//플레이컨트롤러에서 플레이어1,2 등록
	AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC);
	if (MyPC)
	{
		MyPC->RegisterPlayers(Player1, Player2);
	}
}

