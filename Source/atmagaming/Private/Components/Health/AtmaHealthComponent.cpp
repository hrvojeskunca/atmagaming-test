// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Health/AtmaHealthComponent.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"


UAtmaHealthComponent::UAtmaHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = MaxHealth;
}

void UAtmaHealthComponent::BeginPlay()
{
	Super::BeginPlay();

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

		LastDamageTime = GetWorld()->GetTimeSeconds();

		GetWorld()->GetTimerManager().ClearTimer(HealthRegenTimerHandle);

		GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle, this, &UAtmaHealthComponent::RegenerateHealth, HealthRegenInterval, true, HealthRegenDelay);
	}
}

void UAtmaHealthComponent::RegenerateHealth()
{
	if (GetWorld()->GetTimeSeconds() - LastDamageTime >= HealthRegenDelay)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth + HealthRegenRate, 0.0f, MaxHealth);

		if (CurrentHealth >= MaxHealth)
		{
			GetWorld()->GetTimerManager().ClearTimer(HealthRegenTimerHandle);
		}
	}
}

void UAtmaHealthComponent::SetMaxHealth(float NewHealth)
{
	MaxHealth = NewHealth;
}

void UAtmaHealthComponent::SetRegenerationRate(float NewRegenerationRate)
{
	HealthRegenRate = NewRegenerationRate;
}

void UAtmaHealthComponent::SetRegenRateInterval(float NewHealthRegenRateInterval)
{
	HealthRegenInterval = NewHealthRegenRateInterval;
}

void UAtmaHealthComponent::SetRegenRateDelay(float NewHealthRegenRateDelay)
{
	HealthRegenDelay = NewHealthRegenRateDelay;
}
