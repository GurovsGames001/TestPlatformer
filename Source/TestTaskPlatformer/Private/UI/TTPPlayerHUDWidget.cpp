// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TTPPlayerHUDWidget.h"
#include "Components/TTPHealthComponent.h"

void UTTPPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UTTPPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void UTTPPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = GetTTPHealthComponent(NewPawn);
    if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &UTTPPlayerHUDWidget::OnHealthChanged);
    }
}

void UTTPPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
    }
}

float UTTPPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = GetTTPHealthComponent(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool UTTPPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = GetTTPHealthComponent(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool UTTPPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

UTTPHealthComponent* UTTPPlayerHUDWidget::GetTTPHealthComponent(AActor* PlayerPawn) const
{
    if (!PlayerPawn) return nullptr;

    const auto Component = PlayerPawn->GetComponentByClass(UTTPHealthComponent::StaticClass());
    return Cast<UTTPHealthComponent>(Component);
};
