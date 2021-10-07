// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float AxisValue);
	// void LookUp(float AxisValue);
	void Strafe(float AxisValue);
	// void LookRight(float AxisValue);
	// void Jump();
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	void Shoot();

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly)	// We don't want to be able to edit this at runtime
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun = nullptr;
};