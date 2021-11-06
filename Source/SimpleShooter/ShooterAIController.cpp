// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    APawn* PlayerPawn = GetMainPlayerPawn();
    
    if (LineOfSightTo(PlayerPawn))
    {
        MoveToActor(PlayerPawn, AcceptanceRadius);
        SetFocus(PlayerPawn);
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
}

APawn* AShooterAIController::GetMainPlayerPawn() const
{
    return UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}
