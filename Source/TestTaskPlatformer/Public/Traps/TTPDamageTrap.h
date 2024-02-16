// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "TTPDamageTrap.generated.h"

class UBoxComponent;

UCLASS()
class TESTTASKPLATFORMER_API ATTPDamageTrap : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	ATTPDamageTrap();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* TriggerBoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction", meta = (ClampMin = "1", ClampMax = "100"))
		int32 DamageAmount = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Duration", meta = (ClampMin = "1.0", ClampMax = "10.0"))
		float DurationWarningPhase = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Duration", meta = (ClampMin = "1.0", ClampMax = "10.0"))
		float DurationRestartTrap = 5.0f;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnTriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void LaunchTrap();
	void RestartTrap();
	void BlinkRed();
	bool SetColor(const FVector4& NewColor);

	bool IsTrapActive = true;
	float FrequencyBlinking = 0.5f;

	FVector4 RedColor = FVector4(1.0f, 0.0f, 0.0f, 0.0f);
	FVector4 WarningColor = FVector4(1.0f, 0.25f, 0.0f, 0.0f);
	FVector4 DefaultColor = FVector4(1.0f, 1.0f, 1.0f, 0.0f);

	FTimerHandle TimerLaunchTrapHandle;
	FTimerHandle TimerRestartTrapHandle;
	FTimerHandle TimerBlinkRedTrapHandle;
};
