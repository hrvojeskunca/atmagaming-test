// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnBase.h"
#include "WeaponSystem/Weapons/AtmaWeaponBase.h"
#include "Components/SphereComponent.h"


APawnBase::APawnBase()
{

	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(50.0f);
	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	WeaponAttachmentPoint = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponAttachmentPoint"));
	WeaponAttachmentPoint->SetupAttachment(MeshComponent);

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

UChildActorComponent* APawnBase::GetWeaponAttachmentPoint() const
{
	return WeaponAttachmentPoint;
}
