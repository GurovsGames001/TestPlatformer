// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "TTPJumpTrap.generated.h"

class UBoxComponent;

UCLASS()
class TESTTASKPLATFORMER_API ATTPJumpTrap : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ATTPJumpTrap();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* TriggerBoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction", meta = (ClampMin = "1", ClampMax = "2000"))
		int32 LengthJump = 200;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction", meta = (ClampMin = "1", ClampMax = "2000"))
		int32 HeightJump = 700;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Duration", meta = (ClampMin = "0.1", ClampMax = "10.0"))
		float DurationNeutralPhase = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Duration", meta = (ClampMin = "0.1", ClampMax = "10.0"))
		float DurationDangerousPhase = 1.0f;

	virtual void BeginPlay() override;

private:
	void StartNeutralPhase();
	void StartDangerousPhase();
	void DoDangerousPhase();
	bool SetColor(const FVector4& NewColor);

	FVector4 ColorNeutralPhase = FVector4(0.0f, 1.0f, 0.0f, 0.0f);
	FVector4 ColorDangerousPhase = FVector4(1.0f, 0.0f, 0.0f, 0.0f);

	FVector DirectionJumpVector;

	FTimerHandle TimerNextPhaseHandle;
	FTimerHandle TimerDangerousPhaseHandle;
};
