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
}
