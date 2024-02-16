// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TTPGameModeBase.h"
#include "TTPPlayerController.generated.h"

UCLASS()
class TESTTASKPLATFORMER_API ATTPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;
    //virtual void SetupInputComponent() override;

private:
    //void OnPauseGame();
    void OnGameStateChanged(ETTPGameState State);
};
