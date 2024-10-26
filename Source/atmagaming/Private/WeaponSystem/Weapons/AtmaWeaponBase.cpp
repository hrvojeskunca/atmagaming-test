// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Weapons/AtmaWeaponBase.h"


AAtmaWeaponBase::AAtmaWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    MeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	RootComponent = MeshComponent;

}

void AAtmaWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAtmaWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

