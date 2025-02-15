// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

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

	FVector Player1Location(0,200,0);
	ACharacter* Player1 = GetWorld()->SpawnActor<ACharacter>(HwoarangClass, Player1Location, SpawnRotation);
	if(Player1)
	{
		Player1->Tags.Add(FName("Player1")); // 태그 추가 (수정된 부분)
	}
	
	FVector Player2Location(0,200,0);
	ACharacter* Player2 = GetWorld()->SpawnActor<ACharacter>(SteveFoxClass, Player2Location, SpawnRotation);
	if(Player2)
	{
		Player2->Tags.Add(FName("Player2")); // 태그 추가 (수정된 부분)
	}


	
	//카메라 스폰
	FVector CameraLocation(0,100,90);
	FRotator CameraRotation(0,0,0);
	APawn* CameraPawn = GetWorld()->SpawnActor<APawn>(CameraClass,CameraLocation, SpawnRotation);
	

	//카메라 뷰포트 설정
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC && CameraPawn)
	{
		PC->SetViewTarget(CameraPawn);
	}
	//플레이컨트롤러에서 플레이어1,2 등록
	AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC);
	if (MyPC)
	{
		MyPC->RegisterPlayers(Player1, Player2);
	}
	
}

