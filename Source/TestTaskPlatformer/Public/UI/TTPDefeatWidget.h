// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTPGameModeBase.h"
#include "TTPDefeatWidget.generated.h"

class UButton;

UCLASS()
class TESTTASKPLATFORMER_API UTTPDefeatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
        UButton* ResetLevelButton;

    virtual void NativeOnInitialized() override;

private:
    void OnGameStateChanged(ETTPGameState State);

    UFUNCTION()
        void OnResetLevel();
};
