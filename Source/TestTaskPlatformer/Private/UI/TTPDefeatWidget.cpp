// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TTPDefeatWidget.h"
#include "TTPGameModeBase.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTTPDefeatWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<ATTPGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnGameStateChanged.AddUObject(this, &UTTPDefeatWidget::OnGameStateChanged);
        }
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &UTTPDefeatWidget::OnResetLevel);
    }
}

void UTTPDefeatWidget::OnGameStateChanged(ETTPGameState State)
{
    if (State == ETTPGameState::Defeat)
    {

    }
}

void UTTPDefeatWidget::OnResetLevel()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
