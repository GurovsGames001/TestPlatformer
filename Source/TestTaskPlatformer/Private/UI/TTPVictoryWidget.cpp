// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TTPVictoryWidget.h"
#include "TTPGameModeBase.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTTPVictoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetWorld())
	{
		const auto GameMode = Cast<ATTPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnGameStateChanged.AddUObject(this, &UTTPVictoryWidget::OnGameStateChanged);
		}
	}

	if (ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &UTTPVictoryWidget::OnResetLevel);
	}
}

void UTTPVictoryWidget::OnGameStateChanged(ETTPGameState State)
{
	if (State == ETTPGameState::Victory)
	{
		if (!GetWorld()) return;

		const auto GameMode = Cast<ATTPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		PassageTime = GameMode->GetPassageTime();
	}
}

void UTTPVictoryWidget::OnResetLevel()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}