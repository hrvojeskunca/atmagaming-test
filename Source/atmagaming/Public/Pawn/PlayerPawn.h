// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/PawnBase.h"
#include "PlayerPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;

UCLASS()
class ATMAGAMING_API APlayerPawn : public APawnBase
{
	GENERATED_BODY()
	
public:
	APlayerPawn();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Components")
	UFloatingPawnMovement* FloatingPawnMovementComponent;
	
};
