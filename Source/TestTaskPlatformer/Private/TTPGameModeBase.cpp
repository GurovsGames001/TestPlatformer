// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPGameModeBase.h"
#include "Player/TTPBaseCharacter.h"
#include "Player/TTPPlayerController.h"
#include "UI/TTPGameHUD.h"
#include "EngineUtils.h"

ATTPGameModeBase::ATTPGameModeBase()
{
    PlayerControllerClass = ATTPPlayerController::StaticClass();
    DefaultPawnClass = ATTPBaseCharacter::StaticClass();
    HUDClass = ATTPGameHUD::StaticClass();
}

void ATTPGameModeBase::StartPlay()
{
    Super::StartPlay();

    SetGameState(ETTPGameState::InProgress);
}

void ATTPGameModeBase::SetGameState(ETTPGameState State)
{
    if (GameState == State) return;

    GameState = State;
    OnGameStateChanged.Broadcast(GameState);
}

void ATTPGameModeBase::SetDefeat()
{
    SetGameState(ETTPGameState::Defeat);
}

void ATTPGameModeBase::SetVictory()
{
    if (!GetWorld()) return;

    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->DisableInput(nullptr);
        }
    }

    PassageTime = GetWorld()->TimeSince(TimeSpentStart);

    SetGameState(ETTPGameState::Victory);
}

void ATTPGameModeBase::SetTimeSpentStart()
{
    if (!HasPlayerStart && GetWorld())
    {
        HasPlayerStart = true;
        TimeSpentStart = GetWorld()->GetTimeSeconds(); // !!! РАССИНХРОН !!! Возможно нужен таймер
    }
}
