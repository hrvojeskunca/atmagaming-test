// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Bullets/AtmaBasicBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AAtmaBasicBullet::AAtmaBasicBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	MaxSpeed = 800.0f;
	InitialSpeed = 500.0f;
	Damage = 10.0f;
	CallingActorVelocity = FVector::ZeroVector;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>("ProjectileSceneComponent");
	}

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
		CollisionComponent->InitSphereRadius(15.0f);
		CollisionComponent->SetupAttachment(RootComponent);
	}

	if (!MeshComponent)
	{
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
		MeshComponent->SetupAttachment(CollisionComponent);
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComponent");
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed;
		ProjectileMovementComponent->MaxSpeed;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	}

	InitialLifeSpan = 5.0f;

}

void AAtmaBasicBullet::BeginPlay()
{
	Super::BeginPlay();
	
}


void AAtmaBasicBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAtmaBasicBullet::FireInDirection(const FVector& ShootDirection)
{

	ProjectileMovementComponent->Velocity = (ShootDirection * InitialSpeed) + CallingActorVelocity;
}

