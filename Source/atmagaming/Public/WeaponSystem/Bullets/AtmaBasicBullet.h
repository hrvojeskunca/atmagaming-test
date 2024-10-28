// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AtmaBasicBullet.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class ATMAGAMING_API AAtmaBasicBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	AAtmaBasicBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BulletProperties)
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BulletProperties)
	float InitialSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BulletProperties)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BulletProperties)
	FVector CallingActorVelocity;

	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDirection);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(EditAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

};
