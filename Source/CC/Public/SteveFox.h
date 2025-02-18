
#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "GameCharacterState.h" 
#include "SteveFox.generated.h"

UCLASS()
class CC_API ASteveFox : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASteveFox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
