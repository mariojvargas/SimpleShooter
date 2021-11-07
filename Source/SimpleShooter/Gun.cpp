// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values
AGun::AGun()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
    Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
    UE_LOG(LogTemp, Warning, TEXT("You pulled the trigger! Pew! Pew!"));
    UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

    APawn *OwnerPawn = Cast<APawn>(GetOwner());
    if (!OwnerPawn)
    {
        return;
    }

    AController *OwnerController = OwnerPawn->GetController();
    if (!OwnerController)
    {
        return;
    }

    FVector Location;
    FRotator Rotation;
    OwnerController->GetPlayerViewPoint(OUT Location, OUT Rotation);

    FVector End = Location + Rotation.Vector() * MaxRange;

    FCollisionQueryParams IgnoredActors;
    IgnoredActors.AddIgnoredActor(this);
    IgnoredActors.AddIgnoredActor(GetOwner());

    FHitResult HitResult;
    bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(OUT HitResult, Location, End, BulletCollisionChannel, IgnoredActors);
    if (bHitSuccess)
    {
        // DrawDebugCamera(GetWorld(), OUT Location, OUT Rotation, 90, 2, FColor::Red, true);
        // DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);

        FVector ShotDirection = -Rotation.Vector(); // negative indicates where bullet is coming from
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShotDirection.Rotation());

        FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
        AActor *DamagedActor = HitResult.GetActor();
        if (DamagedActor)
        {
            // 	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
            DamagedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
            UE_LOG(LogTemp, Warning, TEXT("Enemy hit %s"), *DamagedActor->GetName());
        }
    }
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
