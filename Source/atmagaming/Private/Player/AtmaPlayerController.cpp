// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AtmaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameData/AtmaPlayerPawnData.h"

AAtmaPlayerController::AAtmaPlayerController()
{
	
}

void AAtmaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledPawn = GetPawn<APawn>();

	check(AtmaContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	check(Subsystem);
	Subsystem->AddMappingContext(AtmaContext, 0);

	bShowMouseCursor = true;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	FAtmaPlayerPawnData PlayerData;
	DefaultSpeed = PlayerData.PlayerValues[FName("DefaultSpeed")];
	Deceleration = PlayerData.PlayerValues[FName("Deceleration")];
	MaxSpeed = PlayerData.PlayerValues[FName("MaxSpeed")];

	AutoMove();

}

void AAtmaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAtmaPlayerController::Move);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::None, this, &AAtmaPlayerController::AutoMove);

}

void AAtmaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

	if (ControlledPawn)
	{
		if (InputAxisVector.Y > 0)
		{
			ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		} 
		else if (InputAxisVector.Y < 0)
		{
			float CurrentSpeed = ControlledPawn->GetVelocity().Size();
			CurrentSpeed = FMath::Max(CurrentSpeed - Deceleration * GetWorld()->GetDeltaSeconds(), 0.f);

			if (CurrentSpeed > 0)
			{
				ControlledPawn->AddMovementInput(ForwardDirection, CurrentSpeed / MaxSpeed);
			}
			else
			{
				ControlledPawn->AddMovementInput(ForwardDirection, 0.f);
			}
		}
		else {
			ControlledPawn->AddMovementInput(ForwardDirection, DefaultSpeed);
		}
		
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAtmaPlayerController::AutoMove()
{	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
	
	if (ControlledPawn)
	{
		ControlledPawn->AddMovementInput(ForwardDirection, DefaultSpeed);
	}
}