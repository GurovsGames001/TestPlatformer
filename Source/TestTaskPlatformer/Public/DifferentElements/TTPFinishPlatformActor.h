// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "TTPFinishPlatformActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class TESTTASKPLATFORMER_API ATTPFinishPlatformActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	ATTPFinishPlatformActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* TriggerBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* FinishLineStaticMeshComponent;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnTriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
