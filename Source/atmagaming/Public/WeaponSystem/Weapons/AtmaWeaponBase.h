// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CombatActions.h"
#include "GameData/Enums/EWeaponType.h"
#include "GameData/Enums/EWeaponFireState.h"
#include "AtmaWeaponBase.generated.h"

class AAtmaBasicBullet;

UCLASS()
class ATMAGAMING_API AAtmaWeaponBase : public AActor, public ICombatActions
{
	GENERATED_BODY()
	
public:	
	AAtmaWeaponBase();

	UPROPERTY(EditAnywhere, Category = DefaultWeaponType)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, Category = DefaultBulletData)
	float WeaponDamage;

	UPROPERTY(EditAnywhere, Category = DefaultBulletData)
	float WeaponCooldown;

	UPROPERTY(EditAnywhere, Category = DefaultBulletData)
	float BulletMaxSpeed;

	UPROPERTY(EditAnywhere, Category = DefaultBulletData)
	float BulletInitialSpeed;

	UPROPERTY(VisibleAnywhere, Category = WeaponData)
    FName EquippedWeaponName;

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

private:
	FTimerHandle BaseWeaponCooldownTimerHandle;
	EWeaponFireState FireState = EWeaponFireState::Ready;

	void ResetFireCooldown();

	void SetWeaponData(FName WeaponName);
	void HandleFireProjectile();
	void FireProjectile();
};
