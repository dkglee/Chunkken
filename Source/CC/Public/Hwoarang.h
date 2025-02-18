
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacterState.h" 
#include "Hwoarang.generated.h"



UCLASS()
class CC_API AHwoarang : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHwoarang();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue = 1, bool bForce = false) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	UBoxComponent* HurtBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="State")
	EGameCharacterState CurrentState;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void Attack();

	UFUNCTION(BlueprintCallable, Category="State")
	void SetState(EGameCharacterState NewState);


};
