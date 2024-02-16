// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TTPBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TTPHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/DamageEvents.h"
#include "TTPGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

ATTPBaseCharacter::ATTPBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.0f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    HealthComponent = CreateDefaultSubobject<UTTPHealthComponent>("HealthComponent");
}

void ATTPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    check(CameraCollisionComponent);
    check(HealthComponent);
    check(GetMesh());

    //OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ATTPBaseCharacter::OnDeath);
    //HealthComponent->OnHealthChanged.AddUObject(this, &ATTPBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ATTPBaseCharacter::OnGroundLanded);

    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATTPBaseCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ATTPBaseCharacter::OnCameraCollisionEndOverlap);
}

void ATTPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATTPBaseCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CheckCameraOverlap();
}

void ATTPBaseCharacter::OnCameraCollisionEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    CheckCameraOverlap();
}

void ATTPBaseCharacter::CheckCameraOverlap()
{
    const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);

    for (auto MeshChild : MeshChildren)
    {
        const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
        if (MeshChildGeometry)
        {
            MeshChildGeometry->SetOwnerNoSee(HideMesh);
        }
    }
}

void ATTPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATTPBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATTPBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ATTPBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ATTPBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATTPBaseCharacter::Jump);

}

void ATTPBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ATTPBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ATTPBaseCharacter::OnDeath()
{
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);

    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        auto GameMode = Cast<ATTPGameModeBase>(GetWorld()->GetAuthGameMode());
        GameMode->SetDefeat();
    }
}

void ATTPBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;
    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);

    UE_LOG(BaseCharacterLog, Display, TEXT("Player %s recived landed damage: %f"), *GetName(), FinalDamage);
}

