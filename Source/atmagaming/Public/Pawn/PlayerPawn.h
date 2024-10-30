// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/PawnBase.h"
#include "PlayerPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ATMAGAMING_API APlayerPawn : public APawnBase
{
	GENERATED_BODY()
	
public:
	APlayerPawn();
	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void SetPawnData(EAtmaPawnType NewPawnType) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = PawnData)
	EAtmaPawnType PawnType;

	UPROPERTY(EditAnywhere, Category = Components)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, Category = Components)
	TObjectPtr<UCameraComponent> Camera;
};
