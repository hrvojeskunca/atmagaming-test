// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnBase.h"
#include "WeaponSystem/Weapons/AtmaWeaponBase.h"
#include "Components/SphereComponent.h"
#include "Interfaces/HealthStatus.h"
#include "Components/Health/AtmaHealthComponent.h"


APawnBase::APawnBase()
{

	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(RootComponent);

	WeaponAttachmentComponent = CreateDefaultSubobject<UChildActorComponent>("WeaponAttachmentComponent");
	WeaponAttachmentComponent->SetupAttachment(MeshComponent);

	if (!HealthComponent)
	{
		HealthComponent = CreateDefaultSubobject<UActorComponent>("HealthComponent");

	}

}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();
}

void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
}

UStaticMeshComponent* APawnBase::GetMesh() const
{
	return MeshComponent;
}

UChildActorComponent* APawnBase::GetWeaponAttachmentComponent() const
{
	return WeaponAttachmentComponent;
}

void APawnBase::ApplyDamage(AActor* DamageActor, float DamageAmount, TSubclassOf<UDamageType> DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HealthComponent->GetClass()->ImplementsInterface(UHealthStatus::StaticClass()))
	{
		IHealthStatus* HealthStatusInterface = CastChecked<IHealthStatus>(HealthComponent);

		HealthStatusInterface->TakeDamage(DamageAmount, DamageType);
	}
}
