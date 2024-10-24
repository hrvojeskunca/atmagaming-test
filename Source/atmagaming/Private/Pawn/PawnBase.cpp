// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnBase.h"


APawnBase::APawnBase()
{

	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());

}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}