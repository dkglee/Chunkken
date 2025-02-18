
#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "GameCharacterState.h" 
#include "Hwoarang.generated.h"

UCLASS()
class CC_API AHwoarang : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHwoarang();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
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
