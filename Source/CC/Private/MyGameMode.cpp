// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

#include "CameraManager.h"
#include "FastLogger.h"
#include "MyPlayerController.h"
#include "Hwoarang.h"
#include "MainUI.h"
#include "NetworkMessage.h"
#include "SteveFox.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


AMyGameMode::AMyGameMode()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();

	DefaultPawnClass = nullptr;
	
	static ConstructorHelpers::FClassFinder<UMainUI> WBP_MainUI
	(TEXT("/Game/Widget/MainHUD/WBP_MainUI.WBP_MainUI_C"));
	if (WBP_MainUI.Succeeded())
	{
		MainUIClass = WBP_MainUI.Class;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> SC_ReadyFight
	(TEXT("/Game/Sound/C_ReadyFight.C_ReadyFight.C_ReadyFight"));
	if (SC_ReadyFight.Succeeded())
	{
		ReadyFightSound = SC_ReadyFight.Object;
	}
		
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	//카메라 스폰
	FVector CameraLocation(0,0,90);
	FRotator CameraRotation(0,0,0);
	ACameraManager* CameraManager = GetWorld()->SpawnActor<ACameraManager>(CameraClass, CameraLocation, CameraRotation);
	
	//플레이어1,2 스폰
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FVector Player1Location(810, -50, -50);
	FRotator Player1Rotation({0, 90, 0});
	ABaseCharacter* Player1 = GetWorld()->SpawnActor<ABaseCharacter>(HwoarangClass, Player1Location, Player1Rotation);
	if(Player1)
	{
		Player1->Tags.Add(FName("Player1")); // 태그 추가 (수정된 부분)
	}
	
	FVector Player2Location(810, 50, -50);
	FRotator Player2Rotation({0, -90, 0});
	ABaseCharacter* Player2 = GetWorld()->SpawnActor<ABaseCharacter>(SteveFoxClass, Player2Location, Player2Rotation);
	if(Player2)
	{
		Player2->Tags.Add(FName("Player2")); // 태그 추가 (수정된 부분)
	}
	
	//카메라 뷰포트 설정
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC && CameraManager)
	{
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

	MyPC->SetInputMode(FInputModeGameOnly());
}

UMainUI* AMyGameMode::GetMainUI()
{
	// UI 생성
	if (!MainUI)
	{
		if (!MainUIClass)
		{
			FFastLogger::LogConsole(TEXT("MainUIClass is nullptr"));
			return nullptr;
		}
		MainUI = CreateWidget<UMainUI>(GetWorld(), MainUIClass);
		MainUI->AddToViewport();

		// 게임 시작 애니메이션 동작
		MainUI->PlayReadyRightAnim();
		UGameplayStatics::PlaySound2D(GetWorld(), ReadyFightSound, 0.5f, 1.0f, 0.0f, nullptr, nullptr);


		FTimerHandle TimerHandle;
		TWeakObjectPtr<AMyGameMode> WeakThis = this;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->bGameStart = true;
			}
		}), 2.5f, false);
	}
	return MainUI;
}

bool AMyGameMode::IsGameStarted()
{
	return bGameStart;
}

void AMyGameMode::GameEnd()
{
	FTimerHandle TimerHandle;
	TWeakObjectPtr<AMyGameMode> WeakThis = this;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis]()
	{
		if (WeakThis.IsValid())
		{
			UGameplayStatics::OpenLevel(WeakThis->GetWorld(), "EndLevel");
		}
	}), 2.0f, false);
}

