// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	if (!SpringArm)
	{
		SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
		SpringArm->SetupAttachment(GetRootComponent());
		SpringArm->TargetArmLength = 600.f;
	}

	if (!Camera)
	{
		Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
		Camera->SetupAttachment(SpringArm);
	}
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	SetPawnData(PawnType);
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetPawnData(EAtmaPawnType NewPawnType)
{
	Super::SetPawnData(NewPawnType);
}
