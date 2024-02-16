// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TTPGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "TTPGameModeBase.h"

void ATTPGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(ETTPGameState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(ETTPGameState::Defeat, CreateWidget<UUserWidget>(GetWorld(), DefeatWidgetClass));
	GameWidgets.Add(ETTPGameState::Victory, CreateWidget<UUserWidget>(GetWorld(), VictoryWidgetClass));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<ATTPGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnGameStateChanged.AddUObject(this, &ATTPGameHUD::OnGameStateChanged);
		}
	}
}

void ATTPGameHUD::OnGameStateChanged(ETTPGameState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}