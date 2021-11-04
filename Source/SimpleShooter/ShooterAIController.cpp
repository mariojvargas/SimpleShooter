// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPawn = GetMainPlayerPawn();
    if (PlayerPawn)
    {
        SetFocus(PlayerPawn);
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    APawn* PlayerPawn = GetMainPlayerPawn();
    if (PlayerPawn)
    {
        MoveToActor(PlayerPawn, 200);
    }
}

APawn* AShooterAIController::GetMainPlayerPawn() const
{
    return UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}
