// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/TTPMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTTPMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UTTPMenuWidget::OnStartGame);
    }
}

void UTTPMenuWidget::OnStartGame()
{
    const FName StartupLevelName = "TestLevel";
    UGameplayStatics::OpenLevel(this, StartupLevelName);
}
