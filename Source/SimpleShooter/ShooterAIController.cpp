// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterAIBlackboardKey.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

     if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);

        GetBlackboardComponent()->SetValueAsVector(ShooterAIBlackboardKey::StartLocation, GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    APawn* PlayerPawn = GetMainPlayerPawn();
    
    if (LineOfSightTo(PlayerPawn))
    {
        GetBlackboardComponent()->SetValueAsVector(ShooterAIBlackboardKey::PlayerLocation, PlayerPawn->GetActorLocation());

        GetBlackboardComponent()->SetValueAsVector(ShooterAIBlackboardKey::LastKnownPlayerLocation, PlayerPawn->GetActorLocation());
    }
    else
    {
        GetBlackboardComponent()->ClearValue(ShooterAIBlackboardKey::PlayerLocation);
    }
}

APawn* AShooterAIController::GetMainPlayerPawn() const
{
    return UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}
