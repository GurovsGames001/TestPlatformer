// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/TTPFallTrap.h"
#include "Components/BoxComponent.h"
#include "Player/TTPBaseCharacter.h"

ATTPFallTrap::ATTPFallTrap()
{
	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	TriggerBoxComponent->SetupAttachment(GetRootComponent());
	TriggerBoxComponent->SetBoxExtent(FVector(150.0f, 150.0f, 27.0f));
	TriggerBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ATTPFallTrap::BeginPlay()
{
	Super::BeginPlay();

	check(TriggerBoxComponent);
	check(GetStaticMeshComponent());

	TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATTPFallTrap::OnTriggerBoxComponentBeginOverlap);
}

void ATTPFallTrap::OnTriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetWorld() && IsTrapActive)
	{
		IsTrapActive = false;
		GetWorld()->GetTimerManager().SetTimer(TimerBlinkRedTrapHandle, this, &ATTPFallTrap::BlinkRed, FrequencyBlinking, false);
		GetWorld()->GetTimerManager().SetTimer(TimerLaunchTrapHandle, this, &ATTPFallTrap::LaunchTrap, DurationWarningPhase, false);
	}
}

void ATTPFallTrap::LaunchTrap()
{
	if (!GetWorld() || !GetStaticMeshComponent()) return;

	GetStaticMeshComponent()->SetVisibility(false);
	GetStaticMeshComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	GetWorld()->GetTimerManager().ClearTimer(TimerBlinkRedTrapHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerRestartTrapHandle, this, &ATTPFallTrap::RestartTrap, DurationRestartTrap, false);
}

void ATTPFallTrap::RestartTrap()
{
	if (GetStaticMeshComponent() && SetColor(DefaultColor))
	{
		IsTrapActive = true;
		GetStaticMeshComponent()->SetVisibility(true);
		GetStaticMeshComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	}
}

void ATTPFallTrap::BlinkRed()
{
	if (GetWorld() && SetColor(RedColor))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerBlinkRedTrapHandle, this, &ATTPFallTrap::BlinkDefaultColor, FrequencyBlinking, false);
	}
}

void ATTPFallTrap::BlinkDefaultColor()
{
	if (GetWorld() && SetColor(DefaultColor))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerBlinkRedTrapHandle, this, &ATTPFallTrap::BlinkRed, FrequencyBlinking, false);
	}
}

bool ATTPFallTrap::SetColor(const FVector4& NewColor)
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
