// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/CombatStatus.h"
#include "GameData/Enums/EAtmaPawnType.h"
#include "PawnBase.generated.h"

class USphereComponent;
class UChildActorComponent;
class UWidgetComponent;
class UFloatingPawnMovement;
class UAtmaHealthComponent;

UCLASS(Abstract)
class ATMAGAMING_API APawnBase : public APawn, public ICombatStatus
{
	GENERATED_BODY()

public:

	APawnBase();

	virtual void Tick(float DeltaTime) override;

	UStaticMeshComponent* GetMesh() const;
	UChildActorComponent* GetWeaponAttachmentComponent() const;
	
	virtual void ApplyDamage(AActor* DamageActor, float DamageAmount, TSubclassOf<UDamageType> DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = PawnData)
	virtual void SetPawnData(EAtmaPawnType PawnType);

	UFUNCTION(BlueprintCallable, Category = PawnData)
	float GetPawnDefaultSpeed() { return DefaultPawnSpeed; }

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = PawnData)
	float DefaultPawnSpeed = 0.f;

	UPROPERTY(EditAnywhere, Category = PawnData)
	EAtmaPawnType PawnType = EAtmaPawnType::Default;

	UPROPERTY(EditAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, Category = Components)
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovementComponent;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TObjectPtr<UChildActorComponent> WeaponAttachmentComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(EditAnywhere, Category = Components)
	TObjectPtr<UAtmaHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, Category = Components)
	TObjectPtr<UWidgetComponent> WidgetComponent;
};
