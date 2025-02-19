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
	void OnMoveLeftHwoarang(const FInputActionValue& Value);
	void OnMoveRightHwoarang(const FInputActionValue& Value);
	void OnJumpHwoarang(const FInputActionValue& Value);
	void OnDownHwoarang(const FInputActionValue& InputActionValue);
	void OnMoveLeftSteveFox(const FInputActionValue& Value);
	void OnMoveRightSteveFox(const FInputActionValue& Value);
	void OnJumpSteveFox(const FInputActionValue& Value);
	void OnDownSteveFox(const FInputActionValue& Value);
	void OnLPHwoarang(const FInputActionValue& InputActionValue);
	void OnRPHwoarang(const FInputActionValue& InputActionValue);
	void OnLKHwoarang(const FInputActionValue& InputActionValue);
	void OnRKHwoarang(const FInputActionValue& InputActionValue);
	void OnLPSteve(const FInputActionValue& InputActionValue);
	void OnRPSteve(const FInputActionValue& InputActionValue);
	void OnLKSteve(const FInputActionValue& InputActionValue);
	void OnRKSteve(const FInputActionValue& InputActionValue);
	
	void OnMoveLeftHwoarangReleased(const FInputActionValue& InputActionValue);
	void OnMoveRightHwoarangReleased(const FInputActionValue& InputActionValue);
	void OnJumpHwoarangReleased(const FInputActionValue& InputActionValue);
	void OnDownHwoarangReleased(const FInputActionValue& InputActionValue);
	void OnLPHwoarangReleased(const FInputActionValue& InputActionValue);
	void OnRPHwoarangReleased(const FInputActionValue& InputActionValue);
	void OnLKHwoarangReleased(const FInputActionValue& InputActionValue);
	void OnRKHwoarangReleased(const FInputActionValue& InputActionValue);
	void OnMoveLeftSteveFoxReleased(const FInputActionValue& InputActionValue);
	void OnMoveRightSteveFoxReleased(const FInputActionValue& InputActionValue);
	void OnJumpSteveFoxReleased(const FInputActionValue& InputActionValue);
	void OnDownSteveFoxReleased(const FInputActionValue& InputActionValue);
	void OnLPSteveReleased(const FInputActionValue& InputActionValue);
	void OnRPSteveReleased(const FInputActionValue& InputActionValue);
	void OnLKSteveReleased(const FInputActionValue& InputActionValue);
	void OnRKSteveReleased(const FInputActionValue& InputActionValue);
	
	// 화랑 입력 매핑
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_Hwoarang;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_MoveLeft_Hwoarang;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_MoveRight_Hwoarang;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_Jump_Hwoarang;

	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_Down_Hwoarang;

	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_LP_Hwoarang;
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_RP_Hwoarang;
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_LK_Hwoarang;
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_RK_Hwoarang;
	
	// 스티브 입력 매핑
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_SteveFox;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|SteveFox")
	UInputAction* IA_MoveLeft_SteveFox;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|SteveFox")
	UInputAction* IA_MoveRight_SteveFox;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|SteveFox")
	UInputAction* IA_Jump_SteveFox;

	UPROPERTY(EditDefaultsOnly, Category="Input|SteveFox")
	UInputAction* IA_Down_SteveFox;

	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_LP_Steve;
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_RP_Steve;
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_LK_Steve;
	UPROPERTY(EditDefaultsOnly, Category="Input|Hwarang")
	UInputAction* IA_RK_Steve;
	
	
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
