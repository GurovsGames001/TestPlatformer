// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "TTPStartPlatformActor.generated.h"

class UBoxComponent;

UCLASS()
class TESTTASKPLATFORMER_API ATTPStartPlatformActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ATTPStartPlatformActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* TriggerBoxComponent;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnTriggerBoxComponentEndOverlap(
			UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
