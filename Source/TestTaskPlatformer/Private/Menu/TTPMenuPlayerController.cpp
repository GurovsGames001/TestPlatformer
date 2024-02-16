// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/TTPMenuPlayerController.h"

void ATTPMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}