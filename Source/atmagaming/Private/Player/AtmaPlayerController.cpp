// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AtmaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameData/AtmaPlayerPawnData.h"
#include "Pawn/PlayerPawn.h"
#include "Interfaces/CombatActions.h"
#include "WeaponSystem/Weapons/AtmaWeaponBase.h"

AAtmaPlayerController::AAtmaPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAtmaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledPawn = GetPawn<APlayerPawn>();
	check(ControlledPawn);

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

	HandleAutoMove();

}

void AAtmaPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MouseToWorldLocation;
	FVector MouseToWorldDirection;

	if (DeprojectMousePositionToWorld(MouseToWorldLocation, MouseToWorldDirection))
	{
		FVector PawnLocation = ControlledPawn->GetActorLocation();

		FVector DirectionToMouseYZ = FVector(0.f, MouseToWorldLocation.Y - PawnLocation.Y, MouseToWorldLocation.Z - PawnLocation.Z).GetSafeNormal();

		float TargetYaw = FMath::RadiansToDegrees(FMath::Atan2(DirectionToMouseYZ.Y, DirectionToMouseYZ.Z));

		FRotator TargetRotation = FRotator(0.f, 0.f, TargetYaw);
		ControlledPawn->SetActorRotation(TargetRotation);
	}

}

void AAtmaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAtmaPlayerController::HandleMove);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::None, this, &AAtmaPlayerController::HandleAutoMove);
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AAtmaPlayerController::HandleFire);

}

void AAtmaPlayerController::HandleMove(const FInputActionValue& InputActionValue)
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

void AAtmaPlayerController::HandleFire(const FInputActionValue& InputActionValue)
{
	AActor* WeaponActor = ControlledPawn->GetWeaponAttachmentComponent()->GetChildActor();
	AAtmaWeaponBase* Weapon = CastChecked<AAtmaWeaponBase>(WeaponActor);

	if (Weapon->GetClass()->ImplementsInterface(UCombatActions::StaticClass()))
	{
		ICombatActions* CombatActions = CastChecked<ICombatActions>(Weapon);
		
		CombatActions->Fire();
	}
}

void AAtmaPlayerController::HandleAutoMove()
{	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
	
	if (ControlledPawn)
	{
		ControlledPawn->AddMovementInput(ForwardDirection, DefaultSpeed);
	}
}