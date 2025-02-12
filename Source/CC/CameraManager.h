// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CameraManager.generated.h"

UCLASS()
class CC_API ACameraManager : public ACameraActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACameraManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* MyCameraComponent;

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	ACharacter* Player_hr;

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	ACharacter* Player_sf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CameraOffset = FVector(-200, 0, 300);
	
};
