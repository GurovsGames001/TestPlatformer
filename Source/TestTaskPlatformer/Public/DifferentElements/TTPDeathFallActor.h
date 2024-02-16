// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTPDeathFallActor.generated.h"

class UBoxComponent;

UCLASS()
class TESTTASKPLATFORMER_API ATTPDeathFallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATTPDeathFallActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* TriggerBoxComponent;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnTriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
