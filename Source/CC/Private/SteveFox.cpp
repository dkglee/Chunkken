// Fill out your copyright notice in the Description page of Project Settings.


#include "SteveFox.h"

#include "Components/BoxComponent.h"

// Sets default values
ASteveFox::ASteveFox()
{
	CharID = 101;

	GetMesh()->SetRelativeLocation({0, 0, -90});
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

// Called when the game starts or when spawned
void ASteveFox::BeginPlay()
{
	Super::BeginPlay();
}
