// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTPGameModeBase.h"
#include "TTPVictoryWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class TESTTASKPLATFORMER_API UTTPVictoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
        float GetPassageTime() const { return PassageTime; };

protected:
    UPROPERTY(meta = (BindWidget))
        UButton* ResetLevelButton;

    virtual void NativeOnInitialized() override;

private:
    void OnGameStateChanged(ETTPGameState State);

    UFUNCTION()
        void OnResetLevel();

    float PassageTime = 0.0f;
};
