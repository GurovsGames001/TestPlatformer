// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TTPGameModeBase.h"
#include "TTPGameHUD.generated.h"

UCLASS()
class TESTTASKPLATFORMER_API ATTPGameHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> DefeatWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> VictoryWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
		TMap<ETTPGameState, UUserWidget*> GameWidgets;

	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;

	void OnGameStateChanged(ETTPGameState State);
};
