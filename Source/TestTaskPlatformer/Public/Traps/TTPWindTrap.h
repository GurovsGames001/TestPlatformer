// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "TTPWindTrap.generated.h"

class UBoxComponent;

UCLASS()
class TESTTASKPLATFORMER_API ATTPWindTrap : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ATTPWindTrap();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* TriggerBoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction", meta = (ClampMin = "1", ClampMax = "2000"))
		int32 StrengthWind = 700;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction", meta = (ClampMin = "0.1", ClampMax = "10.0"))
		float FrequencyWind = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction", meta = (ClampMin = "0.1", ClampMax = "10.0"))
		float FrequencyDirectionChange = 2.0f;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnTriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnTriggerBoxComponentEndOverlap(
			UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void LaunchTrap();
	void ChangeDirectionWind();
	void StopTrap();

	bool IsTrapActive = false;

	FTimerHandle TimerLaunchTrapHandle;
	FTimerHandle TimerChangeDirectionWindHandle;

	FVector DirectionWindVector;
};
