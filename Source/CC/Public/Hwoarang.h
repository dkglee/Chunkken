
#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
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


};
