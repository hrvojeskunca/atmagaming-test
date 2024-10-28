// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Weapons/AtmaWeaponBase.h"
#include "WeaponSystem/Bullets/AtmaBasicBullet.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


AAtmaWeaponBase::AAtmaWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent)
	{
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
		MeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		RootComponent = MeshComponent;
	}

	if (!BulletSpawnPoint)
	{
		BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>("BulletSpawnPoint");
		BulletSpawnPoint->SetupAttachment(MeshComponent);
	}

	CurrentWeaponName = "AtmaWeaponBase";

}

void AAtmaWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	/*
	UDataTable* WeaponDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Data/DataTables/AtmaWeaponTable"));
	if (WeaponDataTable)
	{
		static const FString ContextString(TEXT("WeaponDataContext"));
		FAtmaWeaponData* WeaponData = WeaponDataTable->FindRow<FAtmaWeaponData>(CurrentWeaponName, ContextString);

		if (WeaponData)
		{
			
		}
	}
	*/
	
}

void AAtmaWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAtmaWeaponBase::Fire()
{
	float CustomMaxSpeed = 2000.0f;
	float CustomInitialSpeed = 1200.0f;
	float CustomDamage = 25.0f;
	
	FVector ActorVelocity = GetParentActor()->GetVelocity();

	check(BulletClass);

	FVector BulletSpawnLocation = BulletSpawnPoint->GetComponentLocation();
	FVector FireDirection = GetActorForwardVector();
	FRotator BulletRotation = FireDirection.Rotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	AAtmaBasicBullet* Bullet = GetWorld()->SpawnActor<AAtmaBasicBullet>(BulletClass, BulletSpawnLocation, BulletRotation, SpawnParams);

	if (Bullet)
	{
		Bullet->InitialSpeed = CustomInitialSpeed;
		Bullet->MaxSpeed = CustomMaxSpeed;
		Bullet->Damage = CustomDamage;
		Bullet->CallingActorVelocity = ActorVelocity;
		Bullet->FireInDirection(FireDirection);
	}
}

