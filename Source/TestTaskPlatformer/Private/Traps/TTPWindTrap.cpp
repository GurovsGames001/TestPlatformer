// Fill out your copyright notice in the Description page of Project Settings.

#include "Traps/TTPWindTrap.h"
#include "Components/BoxComponent.h"
#include "Player/TTPBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogWindTrap, All, All);

ATTPWindTrap::ATTPWindTrap()
{
	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>("TriggerBoxComponent");
	TriggerBoxComponent->SetupAttachment(GetRootComponent());
	TriggerBoxComponent->SetBoxExtent(FVector(150.0f, 150.0f, 200.0f));
	TriggerBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ATTPWindTrap::BeginPlay()
{
	Super::BeginPlay();

	check(TriggerBoxComponent);
	check(GetStaticMeshComponent());

	TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATTPWindTrap::OnTriggerBoxComponentBeginOverlap);
	TriggerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ATTPWindTrap::OnTriggerBoxComponentEndOverlap);

	DirectionWindVector = FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), 0);
	GetWorld()->GetTimerManager().SetTimer(TimerChangeDirectionWindHandle, this, &ATTPWindTrap::ChangeDirectionWind, FrequencyDirectionChange, true);
}

void ATTPWindTrap::OnTriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetWorld() && !IsTrapActive)
	{
		IsTrapActive = true;
		GetWorld()->GetTimerManager().SetTimer(TimerLaunchTrapHandle, this, &ATTPWindTrap::LaunchTrap, FrequencyWind, true);
	}
}

void ATTPWindTrap::OnTriggerBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, ATTPBaseCharacter::StaticClass());
	if (OverlappingActors.IsEmpty())
	{
		StopTrap();
	}
}

void ATTPWindTrap::LaunchTrap()
{
	UE_LOG(LogWindTrap, Display, TEXT("Trap works"));

	TArray<AActor*> OverlappingActors;
	TriggerBoxComponent->GetOverlappingActors(OverlappingActors, ATTPBaseCharacter::StaticClass());
	for (const auto OverlappingActor : OverlappingActors)
	{
		const auto OverlappingCharacter = Cast<ATTPBaseCharacter>(OverlappingActor);
		if (!OverlappingCharacter) continue;
		OverlappingCharacter->LaunchCharacter(DirectionWindVector * StrengthWind, false, false);
	}
}

void ATTPWindTrap::ChangeDirectionWind()
{
	DirectionWindVector = FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), 0);
}

void ATTPWindTrap::StopTrap()
{
	UE_LOG(LogWindTrap, Display, TEXT("Trap has stopped"));

	IsTrapActive = false;
	GetWorld()->GetTimerManager().ClearTimer(TimerLaunchTrapHandle);
}
