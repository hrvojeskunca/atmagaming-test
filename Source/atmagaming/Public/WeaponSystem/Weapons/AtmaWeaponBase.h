// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CombatActions.h"
#include "AtmaWeaponBase.generated.h"

class AAtmaBasicBullet;

UCLASS()
class ATMAGAMING_API AAtmaWeaponBase : public AActor, public ICombatActions
{
	GENERATED_BODY()
	
public:	
	AAtmaWeaponBase();

	UPROPERTY(VisibleAnywhere, Category = "WeaponData")
    FName CurrentWeaponName;

	virtual void Tick(float DeltaTime) override;
	virtual void Fire() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, Category = Components)
	TObjectPtr<USceneComponent> BulletSpawnPoint;
	
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AAtmaBasicBullet> BulletClass;
};
