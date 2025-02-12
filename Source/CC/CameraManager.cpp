// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

#include "Player_hr.h"
#include "Player_sf.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ACameraManager::ACameraManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MyCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	RootComponent = MyCameraComponent;
}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayer_hr::StaticClass(), FoundPlayers);
	if (FoundPlayers.Num() > 0)
	{
		Player_hr = Cast<APlayer_hr>(FoundPlayers[0]); 
		UE_LOG(LogTemp, Warning, TEXT("Player_hr 찾음: %s"), *Player_hr->GetName()); 
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player_hr 찾을 수 없음!")); 
	}


	FoundPlayers.Empty(); 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayer_sf::StaticClass(), FoundPlayers);
	if (FoundPlayers.Num() > 0)
	{
		Player_sf = Cast<APlayer_sf>(FoundPlayers[0]); 
		UE_LOG(LogTemp, Warning, TEXT("Player_sf 찾음: %s"), *Player_sf->GetName()); 
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player_sf 찾을 수 없음!")); 
	}
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Player_hr || !Player_sf)
	{
		return;
	}

	//중간지점
	FVector P1Loc = Player_hr->GetActorLocation();
	FVector P2Loc = Player_sf->GetActorLocation();
	FVector Mid=(P1Loc+P2Loc)/2;

	//z축 고정
	Mid.Z = CameraOffset.Z;
	
	//mid + 오프셋
	FVector DesiredLocation = Mid + CameraOffset;
	SetActorLocation(DesiredLocation);

	//두 캐릭터 바라보게
	FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(DesiredLocation, Mid);
	SetActorRotation(LookRot);
}

