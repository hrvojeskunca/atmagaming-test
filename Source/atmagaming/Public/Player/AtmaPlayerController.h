// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AtmaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class APlayerPawn;
struct FInputActionValue;

UCLASS()
class ATMAGAMING_API AAtmaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAtmaPlayerController();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> AtmaContext;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	TObjectPtr<APlayerPawn> ControlledPawn;

	float DefaultSpeed;
	float Deceleration;
	float MaxSpeed;

	void Move(const FInputActionValue& InputActionValue);
	void Fire();
	void AutoMove();
};
