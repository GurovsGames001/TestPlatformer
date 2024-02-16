// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTPPlayerHUDWidget.generated.h"

class UTTPHealthComponent;

UCLASS()
class TESTTASKPLATFORMER_API UTTPPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void OnTakeDamage();

protected:
	virtual void NativeOnInitialized() override;

private:
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* NewPawn);

	UTTPHealthComponent* GetTTPHealthComponent(AActor* PlayerPawn) const;
};
