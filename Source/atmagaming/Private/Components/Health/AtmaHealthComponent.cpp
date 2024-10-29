// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Health/AtmaHealthComponent.h"


UAtmaHealthComponent::UAtmaHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	HealthRegenRate = 0.f;

}

void UAtmaHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}


void UAtmaHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAtmaHealthComponent::TakeDamage(float DamageAmount, TSubclassOf<UDamageType> DamageType)
{
	if (DamageAmount > 0)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
		if (CurrentHealth <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("You are deaded!"));
		}
	}
}

void UAtmaHealthComponent::RegenerateHealth(float HealAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.f, MaxHealth);
}

