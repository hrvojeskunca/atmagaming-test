// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Bullets/AtmaBasicBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AAtmaBasicBullet::AAtmaBasicBullet()
{
	PrimaryActorTick.bCanEverTick = false;

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
	}

	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComponent");
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	}

}

void AAtmaBasicBullet::BeginPlay()
{
	Super::BeginPlay();
	
}


void AAtmaBasicBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

