// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/HealthStatus.h"
#include "AtmaHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATMAGAMING_API UAtmaHealthComponent : public UActorComponent, public IHealthStatus
{
	GENERATED_BODY()

public:	
	UAtmaHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual void TakeDamage(float DamageAmount, TSubclassOf<UDamageType> DamageType) override;

	UFUNCTION(BlueprintCallable, Category = Health)
	void RegenerateHealth(float HealAmount);

	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = Health)
	void SetHealthRegenRate(float NewHealRegenRate) { HealthRegenRate = NewHealRegenRate; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Health)
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = Health)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = Health)
	float HealthRegenRate;
		
};
