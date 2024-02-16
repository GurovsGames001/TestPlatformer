// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestTaskPlatformerGameModeBase.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ESTUMatchState);
//
//UENUM(BlueprintType)
//enum class ESTUMatchState : uint8
//{
//    WaitingToStart = 0,
//    InProgress,
//    Pause,
//    GameOver
//};
//
UCLASS()
class TESTTASKPLATFORMER_API ATestTaskPlatformerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

//public:
//	ATestTaskPlatformerGameModeBase();
//
//    FOnMatchStateChangedSignature OnMatchStateChanged;
//
//private:
//    ESTUMatchState MatchState = ESTUMatchState::InProgress;
//
//    void SetMatchState(ESTUMatchState State);
};
