// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/TTPJumpTrap.h"
#include "Components/BoxComponent.h"
#include "Player/TTPBaseCharacter.h"

ATTPJumpTrap::ATTPJumpTrap()
{
	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	TriggerBoxComponent->SetupAttachment(GetRootComponent());
	TriggerBoxComponent->SetBoxExtent(FVector(150.0f, 150.0f, 27.0f));
	TriggerBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ATTPJumpTrap::BeginPlay()
{
	Super::BeginPlay();

	check(TriggerBoxComponent);
	check(GetStaticMeshComponent());

	StartNeutralPhase();
}

void ATTPJumpTrap::StartNeutralPhase()
{
	if (!GetWorld()) return;
	GetWorld()->GetTimerManager().ClearTimer(TimerDangerousPhaseHandle);

	if (SetColor(ColorNeutralPhase))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerNextPhaseHandle, this, &ATTPJumpTrap::StartDangerousPhase, DurationNeutralPhase, false);
	}
}

void ATTPJumpTrap::StartDangerousPhase()
{
	if (SetColor(ColorDangerousPhase))
	{
		if (!GetWorld()) return;

		DirectionJumpVector = FVector(FMath::RandRange(-1.0f, 1.0f) * LengthJump, FMath::RandRange(-1.0f, 1.0f) * LengthJump, HeightJump);

		GetWorld()->GetTimerManager().SetTimer(TimerDangerousPhaseHandle, this, &ATTPJumpTrap::DoDangerousPhase, 0.001, true);
		GetWorld()->GetTimerManager().SetTimer(TimerNextPhaseHandle, this, &ATTPJumpTrap::StartNeutralPhase, DurationDangerousPhase, false);
	}
}

void ATTPJumpTrap::DoDangerousPhase()
{
	TArray<AActor*> OverlappingActors;
	TriggerBoxComponent->GetOverlappingActors(OverlappingActors, ATTPBaseCharacter::StaticClass());
	for (auto OverlappingActor : OverlappingActors)
	{
		const auto OverlappingCharacter = Cast<ATTPBaseCharacter>(OverlappingActor);
		if (!OverlappingCharacter) continue;
		OverlappingCharacter->LaunchCharacter(DirectionJumpVector, false, false);
	}
}

bool ATTPJumpTrap::SetColor(const FVector4& NewColor)
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
