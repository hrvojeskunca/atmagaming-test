// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameData/Maps/AtmaPlayerDataMap.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600.f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");

	if (FloatingPawnMovementComponent)
	{
		FAtmaPlayerDataMap PlayerData;
		TArray<FName> RequiredKeys = { FName("MaxSpeed"), FName("Acceleration"), FName("Deceleration") };
		bool bAllKeysExist = true;

		for (const FName& Key : RequiredKeys)
		{
			if (!PlayerData.PlayerValues.Contains(Key))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s is missing in PlayerValues!"), *Key.ToString());
				bAllKeysExist = false;
			}
		}

		if (bAllKeysExist)
		{
			FloatingPawnMovementComponent->MaxSpeed = PlayerData.PlayerValues[FName("MaxSpeed")];
			FloatingPawnMovementComponent->Acceleration = PlayerData.PlayerValues[FName("Acceleration")];
			FloatingPawnMovementComponent->Deceleration = PlayerData.PlayerValues[FName("Deceleration")];
		}
	}
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
