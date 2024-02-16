// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TTPPlayerController.h"
#include "TTPGameModeBase.h"

void ATTPPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        const auto GameMode = Cast<ATTPGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnGameStateChanged.AddUObject(this, &ATTPPlayerController::OnGameStateChanged);
        }
    }
}

void ATTPPlayerController::OnGameStateChanged(ETTPGameState State)
{
    if (State == ETTPGameState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ATTPPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}

//void ATTPPlayerController::SetupInputComponent()
//{
//    Super::SetupInputComponent();
//    if (!InputComponent) return;
//
//    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
//}

//void ATTPPlayerController::OnPauseGame()
//{
//    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
//
//    GetWorld()->GetAuthGameMode()->SetPause(this);
//}