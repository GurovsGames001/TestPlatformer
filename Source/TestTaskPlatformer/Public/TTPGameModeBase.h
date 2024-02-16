// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TTPGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ETTPGameState);

UENUM(BlueprintType)
enum class ETTPGameState : uint8
{
    WaitingToStart = 0,
    InProgress,
    Pause,
    Defeat,
    Victory
};

UCLASS()
class TESTTASKPLATFORMER_API ATTPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    ATTPGameModeBase();

    FOnMatchStateChangedSignature OnGameStateChanged;

    virtual void StartPlay() override;
    void SetDefeat();
    void SetVictory();

    float GetPassageTime() { return PassageTime; };
    void SetTimeSpentStart();

private:
    ETTPGameState GameState = ETTPGameState::WaitingToStart;

    void SetGameState(ETTPGameState State);

    float TimeSpentStart = 0.0f;
    float PassageTime = 0.0f;

    bool HasPlayerStart = false;
};
