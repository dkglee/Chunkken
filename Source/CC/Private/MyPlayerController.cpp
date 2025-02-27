#include "MyPlayerController.h"

#include "CC.h"
#include "FastLogger.h"
#include "FrameManager.h"
#include "Hwoarang.h"
#include "InputParser.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Pawn.h"
#include "CameraManager.h"
#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
    //화랑 입력
    ConstructorHelpers::FObjectFinder<UInputMappingContext> TempIMCHwoarang(TEXT("/Game/Inputs/IMC_Hwoarang.IMC_Hwoarang"));
    if (TempIMCHwoarang.Succeeded())
    {
        IMC_Hwoarang = TempIMCHwoarang.Object;
    }
    
    ConstructorHelpers::FObjectFinder<UInputAction> TempIALeftHwoarang(TEXT("/Game/Inputs/IA_MoveLeft_Hwoarang.IA_MoveLeft_Hwoarang"));
    if (TempIALeftHwoarang.Succeeded())
    {
        IA_MoveLeft_Hwoarang = TempIALeftHwoarang.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIARightHwoarang(TEXT("/Game/Inputs/IA_MoveRight_Hwoarang.IA_MoveRight_Hwoarang"));
    if (TempIARightHwoarang.Succeeded())
    {
        IA_MoveRight_Hwoarang = TempIARightHwoarang.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIAJumpHwoarang(TEXT("/Game/Inputs/IA_Jump_Hwoarang.IA_Jump_Hwoarang"));
    if (TempIAJumpHwoarang.Succeeded())
    {
        IA_Jump_Hwoarang = TempIAJumpHwoarang.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIADownHwoarang(TEXT("/Game/Inputs/IA_Down_Hwoarang.IA_Down_Hwoarang"));
    if (TempIADownHwoarang.Succeeded())
    {
        IA_Down_Hwoarang = TempIADownHwoarang.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> TempIALPHwoarang(TEXT("/Game/Inputs/IA_LP_Hwoarang.IA_LP_Hwoarang"));
    if (TempIALPHwoarang.Succeeded())
    {
        IA_LP_Hwoarang = TempIALPHwoarang.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> TempIARPHwoarang(TEXT("/Game/Inputs/IA_RP_Hwoarang.IA_RP_Hwoarang"));
    if (TempIARPHwoarang.Succeeded())
    {
        IA_RP_Hwoarang = TempIARPHwoarang.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> TempIALKHwoarang(TEXT("/Game/Inputs/IA_LK_Hwoarang.IA_LK_Hwoarang"));
    if (TempIALKHwoarang.Succeeded())
    {
        IA_LK_Hwoarang = TempIALKHwoarang.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> TempIARKHwoarang(TEXT("/Game/Inputs/IA_RK_Hwoarang.IA_RK_Hwoarang"));
    if (TempIARKHwoarang.Succeeded())
    {
        IA_RK_Hwoarang = TempIARKHwoarang.Object;
    }
    
    //스티브폭스 입력
    ConstructorHelpers::FObjectFinder<UInputMappingContext> TempIMCSteveFox(TEXT("/Game/Inputs/IMC_SteveFox.IMC_SteveFox"));
    if (TempIMCSteveFox.Succeeded())
    {
        IMC_SteveFox = TempIMCSteveFox.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIALeftSteveFox(TEXT("/Game/Inputs/IA_MoveLeft_SteveFox.IA_MoveLeft_SteveFox"));
    if (TempIALeftSteveFox.Succeeded())
    {
        IA_MoveLeft_SteveFox = TempIALeftSteveFox.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIARightSteveFox(TEXT("/Game/Inputs/IA_MoveRight_SteveFox.IA_MoveRight_SteveFox"));
    if (TempIARightSteveFox.Succeeded())
    {
        IA_MoveRight_SteveFox = TempIARightSteveFox.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIAJumpSteveFox(TEXT("/Game/Inputs/IA_Jump_SteveFox.IA_Jump_SteveFox"));
    if (TempIAJumpSteveFox.Succeeded())
    {
        IA_Jump_SteveFox = TempIAJumpSteveFox.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIADownSteveFox(TEXT("/Game/Inputs/IA_Down_SteveFox.IA_Down_SteveFox"));
    if (TempIADownSteveFox.Succeeded())
    {
        IA_Down_SteveFox = TempIADownSteveFox.Object;
    }
    
    ConstructorHelpers::FObjectFinder<UInputAction> TempIALPSteve(TEXT("/Game/Inputs/IA_LP_Steve.IA_LP_Steve"));
    if (TempIALPSteve.Succeeded())
    {
        IA_LP_Steve = TempIALPSteve.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> TempIARPSteve(TEXT("/Game/Inputs/IA_RP_Steve.IA_RP_Steve"));
    if (TempIARPSteve.Succeeded())
    {
        IA_RP_Steve = TempIARPSteve.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> TempIALKSteve(TEXT("/Game/Inputs/IA_LK_Steve.IA_LK_Steve"));
    if (TempIALKSteve.Succeeded())
    {
        IA_LK_Steve = TempIALKSteve.Object;
    }

    ConstructorHelpers::FObjectFinder<UInputAction> TempIARKSteve(TEXT("/Game/Inputs/IA_RK_Steve.IA_RK_Steve"));
    if (TempIARKSteve.Succeeded())
    {
        IA_RK_Steve = TempIARKSteve.Object;
    }

    FrameManager = CreateDefaultSubobject<UFrameManager>(TEXT("FrameManager"));
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
        	if (IMC_Hwoarang)
        	{
        		Subsystem->AddMappingContext(IMC_Hwoarang, 0);
        	}
            if (IMC_SteveFox)
            {
                Subsystem->AddMappingContext(IMC_SteveFox, 0);
            }
            if (IMC_CameraManager)
            {
                Subsystem->AddMappingContext(IMC_CameraManager, 0);
            }
        }
    }
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            UE_LOG(LogTemp, Warning, TEXT("Enhanced Input System Activated"));
        }
    }
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        //카메라 테스트
        if (IA_CameraWeakShake)
        {
            EnhancedInput->BindAction(IA_CameraWeakShake, ETriggerEvent::Triggered, this, &AMyPlayerController::TriggerWeakShake);
        }
        if (IA_CameraStrongShake)
        {
            EnhancedInput->BindAction(IA_CameraStrongShake, ETriggerEvent::Triggered, this, &AMyPlayerController::TriggerStrongShake);
        }
        if (IA_CameraLandingShake)
        {
            EnhancedInput->BindAction(IA_CameraLandingShake, ETriggerEvent::Triggered, this, &AMyPlayerController::TriggerLandingShake);
        }

        // 화랑 입력 바인딩
        if (IA_MoveLeft_Hwoarang)
        {
            EnhancedInput->BindAction(IA_MoveLeft_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMoveLeftHwoarang);
            EnhancedInput->BindAction(IA_MoveLeft_Hwoarang, ETriggerEvent::Completed, this, &AMyPlayerController::OnMoveLeftHwoarangReleased);
        }
        if (IA_MoveRight_Hwoarang)
        {
            EnhancedInput->BindAction(IA_MoveRight_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMoveRightHwoarang);
            EnhancedInput->BindAction(IA_MoveRight_Hwoarang, ETriggerEvent::Completed, this, &AMyPlayerController::OnMoveRightHwoarangReleased);
        }
        if (IA_Jump_Hwoarang)
        {
            EnhancedInput->BindAction(IA_Jump_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnJumpHwoarang);
            EnhancedInput->BindAction(IA_Jump_Hwoarang, ETriggerEvent::Completed, this, &AMyPlayerController::OnJumpHwoarangReleased);
        }
        if (IA_Down_Hwoarang)
        {
            EnhancedInput->BindAction(IA_Down_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnDownHwoarang);
            EnhancedInput->BindAction(IA_Down_Hwoarang, ETriggerEvent::Completed, this, &AMyPlayerController::OnDownHwoarangReleased);
        }
        if (IA_LP_Hwoarang)
        {
            EnhancedInput->BindAction(IA_LP_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnLPHwoarang);
            EnhancedInput->BindAction(IA_LP_Hwoarang, ETriggerEvent::Completed, this, &AMyPlayerController::OnLPHwoarangReleased);
        }
        if (IA_RP_Hwoarang)
        {
            EnhancedInput->BindAction(IA_RP_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnRPHwoarang);
            EnhancedInput->BindAction(IA_RP_Hwoarang, ETriggerEvent::Completed, this, &AMyPlayerController::OnRPHwoarangReleased);
        }
        if (IA_LK_Hwoarang)
        {
            EnhancedInput->BindAction(IA_LK_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnLKHwoarang);
            EnhancedInput->BindAction(IA_LK_Hwoarang, ETriggerEvent::Completed, this, &AMyPlayerController::OnLKHwoarangReleased);
        }
        if (IA_RK_Hwoarang)
        {
            EnhancedInput->BindAction(IA_RK_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnRKHwoarang);
            EnhancedInput->BindAction(IA_RK_Hwoarang, ETriggerEvent::Completed, this, &AMyPlayerController::OnRKHwoarangReleased);
        }

        // 스티브폭스 입력 바인딩
        if (IA_MoveLeft_SteveFox)
        {
            EnhancedInput->BindAction(IA_MoveLeft_SteveFox, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMoveLeftSteveFox);
            EnhancedInput->BindAction(IA_MoveLeft_SteveFox, ETriggerEvent::Completed, this, &AMyPlayerController::OnMoveLeftSteveFoxReleased);
        }
        if (IA_MoveRight_SteveFox)
        {
            EnhancedInput->BindAction(IA_MoveRight_SteveFox, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMoveRightSteveFox);
            EnhancedInput->BindAction(IA_MoveRight_SteveFox, ETriggerEvent::Completed, this, &AMyPlayerController::OnMoveRightSteveFoxReleased);
        }
        if (IA_Jump_SteveFox)
        {
            EnhancedInput->BindAction(IA_Jump_SteveFox, ETriggerEvent::Triggered, this, &AMyPlayerController::OnJumpSteveFox);
            EnhancedInput->BindAction(IA_Jump_SteveFox, ETriggerEvent::Completed, this, &AMyPlayerController::OnJumpSteveFoxReleased);
        }
        if (IA_Down_SteveFox)
        {
            EnhancedInput->BindAction(IA_Down_SteveFox, ETriggerEvent::Triggered, this, &AMyPlayerController::OnDownSteveFox);
            EnhancedInput->BindAction(IA_Down_SteveFox, ETriggerEvent::Completed, this, &AMyPlayerController::OnDownSteveFoxReleased);
        }
        if (IA_LP_Steve)
        {
            EnhancedInput->BindAction(IA_LP_Steve, ETriggerEvent::Triggered, this, &AMyPlayerController::OnLPSteve);
            EnhancedInput->BindAction(IA_LP_Steve, ETriggerEvent::Completed, this, &AMyPlayerController::OnLPSteveReleased);
        }
        if (IA_RP_Steve)
        {
            EnhancedInput->BindAction(IA_RP_Steve, ETriggerEvent::Triggered, this, &AMyPlayerController::OnRPSteve);
            EnhancedInput->BindAction(IA_RP_Steve, ETriggerEvent::Completed, this, &AMyPlayerController::OnRPSteveReleased);
        }
        if (IA_LK_Steve)
        {
            EnhancedInput->BindAction(IA_LK_Steve, ETriggerEvent::Triggered, this, &AMyPlayerController::OnLKSteve);
            EnhancedInput->BindAction(IA_LK_Steve, ETriggerEvent::Completed, this, &AMyPlayerController::OnLKSteveReleased);
        }
        if (IA_RK_Steve)
        {
            EnhancedInput->BindAction(IA_RK_Steve, ETriggerEvent::Triggered, this, &AMyPlayerController::OnRKSteve);
            EnhancedInput->BindAction(IA_RK_Steve, ETriggerEvent::Completed, this, &AMyPlayerController::OnRKSteveReleased);
        }
    }
}

void AMyPlayerController::TriggerWeakShake(const FInputActionValue& Value)
{
    if (CameraManager)
    {
        CameraManager->TriggerWeakShake(1.0f);
        UE_LOG(LogTemp, Warning, TEXT("TriggerWeakShake called"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TriggerWeakShake failed - CameraManager is NULL!"));
    }
}

void AMyPlayerController::TriggerStrongShake(const FInputActionValue& Value)
{
    if (CameraManager)
    {
        CameraManager->TriggerStrongShake();
        UE_LOG(LogTemp, Warning, TEXT("TriggerStrongShake called"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TriggerStrongShake failed - CameraManager is NULL!"));
    }
}

void AMyPlayerController::TriggerLandingShake(const FInputActionValue& Value)
{
    if (CameraManager)
    {
        CameraManager->TriggerLandingShake();
        UE_LOG(LogTemp, Warning, TEXT("TriggerLandingShake called"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TriggerLandingShake failed - CameraManager is NULL!"));
    }
}

void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FrameManager->UpdateFrame(DeltaTime);

    uint64 FrameIndex = FrameManager->GetFrameIndex();
    if (Player1 && Player2)
    {
        Player1->Update(FrameIndex);
        Player2->Update(FrameIndex);
    }
}

void AMyPlayerController::RegisterPlayers(ABaseCharacter* InPlayer1, ABaseCharacter* InPlayer2)
{
    Player1 = InPlayer1;
    Player2 = InPlayer2;
}

//화랑 입력 함수
void AMyPlayerController::OnMoveRightHwoarang(const FInputActionValue& Value)
{
    float ActionValue = Value.Get<float>();
    
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RIGHT);
    Player1->OnPressedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnMoveLeftHwoarang(const FInputActionValue& Value)
{
    float ActionValue = Value.Get<float>();
    
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    
    int32 InputID = UInputParser::GetIndex(LEFT);
    Player1->OnPressedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnJumpHwoarang(const FInputActionValue& Value)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(UP);
    Player1->OnPressedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnDownHwoarang(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(DOWN);
    Player1->OnPressedInput(InputID, FrameManager->GetFrameIndex(), true);
}

//스티브폭스 입력 함수
void AMyPlayerController::OnMoveRightSteveFox(const FInputActionValue& Value)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());float ActionValue = Value.Get<float>();
    
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RIGHT);
    Player2->OnPressedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnMoveLeftSteveFox(const FInputActionValue& Value)
{
    float ActionValue = Value.Get<float>();
    
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LEFT);
    Player2->OnPressedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnJumpSteveFox(const FInputActionValue& Value)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    
    int32 InputID = UInputParser::GetIndex(UP);
    Player2->OnPressedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnDownSteveFox(const FInputActionValue& Value)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(DOWN);
    Player2->OnPressedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnLPHwoarang(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LP);
    Player1->OnPressedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnRPHwoarang(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RP);
    Player1->OnPressedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnLKHwoarang(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LK);
    Player1->OnPressedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnRKHwoarang(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RK);
    Player1->OnPressedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnLPSteve(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LP);
    Player2->OnPressedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnRPSteve(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RP);
    Player2->OnPressedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnLKSteve(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LK);
    Player2->OnPressedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnRKSteve(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RK);
    Player2->OnPressedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnMoveLeftHwoarangReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LEFT);
    Player1->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnMoveRightHwoarangReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RIGHT);
    Player1->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnJumpHwoarangReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(UP);
    Player1->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnDownHwoarangReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(DOWN);
    Player1->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnLPHwoarangReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LP);
    Player1->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnRPHwoarangReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RP);
    Player1->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnLKHwoarangReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LK);
    Player1->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnRKHwoarangReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player1)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RK);
    Player1->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), true);
}

void AMyPlayerController::OnMoveLeftSteveFoxReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LEFT);
    Player2->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnMoveRightSteveFoxReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RIGHT);
    Player2->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnJumpSteveFoxReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(UP);
    Player2->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnDownSteveFoxReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(DOWN);
    Player2->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnLPSteveReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LP);
    Player2->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnRPSteveReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RP);
    Player2->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnLKSteveReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(LK);
    Player2->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), false);
}

void AMyPlayerController::OnRKSteveReleased(const FInputActionValue& InputActionValue)
{
    AMyGameMode* GM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
    if (!GM->IsGameStarted())
    {
        return ;
    }
    if (!Player2)
    {
        return ;
    }
    int32 InputID = UInputParser::GetIndex(RK);
    Player2->OnReleasedInput(InputID, FrameManager->GetFrameIndex(), false);
}
