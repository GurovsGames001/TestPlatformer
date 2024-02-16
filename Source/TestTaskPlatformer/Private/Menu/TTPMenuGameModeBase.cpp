// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/TTPMenuGameModeBase.h"
#include "Menu/TTPMenuPlayerController.h"
#include "Menu/UI/TTPMenuHUD.h"

ATTPMenuGameModeBase::ATTPMenuGameModeBase()
{
    PlayerControllerClass = ATTPMenuPlayerController::StaticClass();
    HUDClass = ATTPMenuHUD::StaticClass();
}
