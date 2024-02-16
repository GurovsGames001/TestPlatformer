// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/TTPDamageTrap.h"
#include "Components/BoxComponent.h"
#include "Player/TTPBaseCharacter.h"
#include "Engine/DamageEvents.h"

ATTPDamageTrap::ATTPDamageTrap()
{
	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	TriggerBoxComponent->SetupAttachment(GetRootComponent());
	TriggerBoxComponent->SetBoxExtent(FVector(150.0f, 150.0f, 27.0f));
	TriggerBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ATTPDamageTrap::BeginPlay()
{
	Super::BeginPlay();

	check(TriggerBoxComponent);
	check(GetStaticMeshComponent());

	TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATTPDamageTrap::OnTriggerBoxComponentBeginOverlap);
}

void ATTPDamageTrap::OnTriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetWorld() && IsTrapActive && SetColor(WarningColor))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerLaunchTrapHandle, this, &ATTPDamageTrap::LaunchTrap, DurationWarningPhase, false);
	}
}

void ATTPDamageTrap::LaunchTrap()
{
	if (GetWorld() && SetColor(RedColor))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerBlinkRedTrapHandle, this, &ATTPDamageTrap::BlinkRed, FrequencyBlinking, false);

		TArray<AActor*> OverlappingActors;
		TriggerBoxComponent->GetOverlappingActors(OverlappingActors, ATTPBaseCharacter::StaticClass());
		for (auto OverlappingActor : OverlappingActors)
		{
			if (!OverlappingActor) continue;
			OverlappingActor->TakeDamage(DamageAmount, FDamageEvent{}, nullptr, this);
		}

		IsTrapActive = false;
		GetWorld()->GetTimerManager().SetTimer(TimerRestartTrapHandle, this, &ATTPDamageTrap::RestartTrap, DurationRestartTrap, false);
	}
}

void ATTPDamageTrap::RestartTrap()
{
	IsTrapActive = true;
}

void ATTPDamageTrap::BlinkRed()
{
	SetColor(DefaultColor);
}

bool ATTPDamageTrap::SetColor(const FVector4& NewColor)
{
	if (GetStaticMeshComponent())
	{
		UMaterialInstanceDynamic* DynMaterial = GetStaticMeshComponent()->CreateAndSetMaterialInstanceDynamic(0);

		if (DynMaterial)
		{
			DynMaterial->SetVectorParameterValue("Color", NewColor);
			return true;
		}
	}

	return false;
}