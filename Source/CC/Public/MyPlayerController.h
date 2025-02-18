#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "MyPlayerController.generated.h"

UCLASS()
class CC_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	//게임모드에서 플레이어 호출
	UFUNCTION(BlueprintCallable, Category="Player")

	void OnMoveLeftHwoarang(const FInputActionValue& Value);
	void OnMoveRightHwoarang(const FInputActionValue& Value);
	void OnJumpHwoarang(const FInputActionValue& Value);
	void OnMoveLeftSteveFox(const FInputActionValue& Value);
	void OnMoveRightSteveFox(const FInputActionValue& Value);
	void OnJumpSteveFox(const FInputActionValue& Value);
	
	// 화랑 입력 매핑
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_Hwoarang;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_MoveLeft_Hwoarang;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_MoveRight_Hwoarang;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_Jump_Hwoarang;
	
	// 스티브 입력 매핑
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_SteveFox;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|SteveFox")
	UInputAction* IA_MoveLeft_SteveFox;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|SteveFox")
	UInputAction* IA_MoveRight_SteveFox;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|SteveFox")
	UInputAction* IA_Jump_SteveFox;
	
public:
	void RegisterPlayers(class ABaseCharacter* InPlayer1, class ABaseCharacter* InPlayer2) ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player")
	class ABaseCharacter* Player1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player")
	class ABaseCharacter* Player2;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player")
	class UFrameManager* FrameManager;
};
