// Fill out your copyright notice in the Description page of Project Settings.


#include "DifferentElements/TTPDeathFallActor.h"
#include "Components/BoxComponent.h"
#include "Player/TTPBaseCharacter.h"
#include "Components/TTPHealthComponent.h"
#include "Engine/DamageEvents.h"

ATTPDeathFallActor::ATTPDeathFallActor()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>("TriggerBoxComponent");
	TriggerBoxComponent->SetupAttachment(GetRootComponent());
	TriggerBoxComponent->SetBoxExtent(FVector(10000.0f, 10000.0f, 10.0f));
	TriggerBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ATTPDeathFallActor::BeginPlay()
{
	Super::BeginPlay();
	
	check(TriggerBoxComponent);

	TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATTPDeathFallActor::OnTriggerBoxComponentBeginOverlap);
}

void ATTPDeathFallActor::OnTriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetWorld()) return;

	const auto Player = Cast<ATTPBaseCharacter>(OtherActor);
	if (!Player) return;

	const auto HealthComponent = Cast<UTTPHealthComponent>(Player->GetComponentByClass(UTTPHealthComponent::StaticClass()));
	if (!HealthComponent) return;

	float DamageAmount = HealthComponent->GetHealth();
	Player->TakeDamage(DamageAmount, FDamageEvent{}, nullptr, nullptr);
}

