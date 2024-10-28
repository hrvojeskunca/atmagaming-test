// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Weapons/AtmaWeaponBase.h"
#include "WeaponSystem/Bullets/AtmaBasicBullet.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameData/Structs/AtmaWeaponData.h"


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

	EquippedWeaponName = "AtmaWeaponBase";
}

void AAtmaWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	SetWeaponData(EquippedWeaponName);
}

void AAtmaWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAtmaWeaponBase::Fire()
{	
	switch (WeaponType)
	{
	case EWeaponType::Projectile:
		HandleFireProjectile();
		break;

	case EWeaponType::Hitscan:
		UE_LOG(LogTemp, Warning, TEXT("Pew! Pew! Railgun hit!"));
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Weapon Data missing! Check WeaponData data table!"));
		break;
	}
}

void AAtmaWeaponBase::SetWeaponData(FName WeaponName)
{
	UDataTable* WeaponDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DataTables/WeaponData"));
	if (WeaponDataTable)
	{
		static const FString ContextString(TEXT("WeaponDataContext"));
		FAtmaWeaponData* WeaponData = WeaponDataTable->FindRow<FAtmaWeaponData>(WeaponName, ContextString);

		if (WeaponData)
		{
			WeaponType = WeaponData->WeaponType;
			WeaponDamage = WeaponData->WeaponDamage;
			WeaponCooldown = WeaponData->WeaponCooldown;
			BulletMaxSpeed = WeaponData->BulletMaxSpeed;
			BulletInitialSpeed = WeaponData->BulletInitialSpeed;
		}
	}
}

void AAtmaWeaponBase::HandleFireProjectile()
{
	switch (FireState)
	{
	case EWeaponFireState::Ready:
		FireProjectile();
		FireState = EWeaponFireState::Cooldown;
		GetWorld()->GetTimerManager().SetTimer(BaseWeaponCooldownTimerHandle, this, &AAtmaWeaponBase::ResetFireCooldown, WeaponCooldown, false);
		break;
	case EWeaponFireState::Cooldown:
		break;
	default:
		break;
	}
}

void AAtmaWeaponBase::FireProjectile()
{
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
		Bullet->InitialSpeed = BulletInitialSpeed;
		Bullet->MaxSpeed = BulletMaxSpeed;
		Bullet->Damage = WeaponDamage;
		Bullet->CallingActorVelocity = ActorVelocity;
		Bullet->FireInDirection(FireDirection);
	}
}

void AAtmaWeaponBase::ResetFireCooldown()
{
	FireState = EWeaponFireState::Ready;
}

