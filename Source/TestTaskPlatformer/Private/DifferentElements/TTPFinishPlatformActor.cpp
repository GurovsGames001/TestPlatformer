// Fill out your copyright notice in the Description page of Project Settings.


#include "DifferentElements/TTPFinishPlatformActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TTPGameModeBase.h"

ATTPFinishPlatformActor::ATTPFinishPlatformActor()
{
	FinishLineStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("FinishLineStaticMeshComponent");
	FinishLineStaticMeshComponent->SetupAttachment(GetRootComponent());
	FinishLineStaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>("TriggerBoxComponent");
	TriggerBoxComponent->SetupAttachment(FinishLineStaticMeshComponent);
	TriggerBoxComponent->SetBoxExtent(FVector(450.0f, 450.0f, 200.0f));
	TriggerBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

void ATTPFinishPlatformActor::BeginPlay()
{
	Super::BeginPlay();

	check(TriggerBoxComponent);

	TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATTPFinishPlatformActor::OnTriggerBoxComponentBeginOverlap);
}

void ATTPFinishPlatformActor::OnTriggerBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetWorld()) return;

	const auto GameMode = Cast<ATTPGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->SetVictory();
}