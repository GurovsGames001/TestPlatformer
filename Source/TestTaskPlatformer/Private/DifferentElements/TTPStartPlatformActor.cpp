// Fill out your copyright notice in the Description page of Project Settings.


#include "DifferentElements/TTPStartPlatformActor.h"
#include "Components/BoxComponent.h"
#include "TTPGameModeBase.h"

ATTPStartPlatformActor::ATTPStartPlatformActor()
{
	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>("TriggerBoxComponent");
	TriggerBoxComponent->SetupAttachment(GetRootComponent());
	TriggerBoxComponent->SetBoxExtent(FVector(500.0f, 500.0f, 200.0f));
	TriggerBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ATTPStartPlatformActor::BeginPlay()
{
	Super::BeginPlay();

	check(TriggerBoxComponent);

	TriggerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ATTPStartPlatformActor::OnTriggerBoxComponentEndOverlap);
}

void ATTPStartPlatformActor::OnTriggerBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!GetWorld()) return;

	const auto GameMode = Cast<ATTPGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->SetTimeSpentStart();
}
