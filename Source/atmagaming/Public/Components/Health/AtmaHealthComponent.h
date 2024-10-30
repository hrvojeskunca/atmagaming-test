// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/HealthStatus.h"
#include "AtmaHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class ATMAGAMING_API UAtmaHealthComponent : public UActorComponent, public IHealthStatus
{
	GENERATED_BODY()

public:	
	UAtmaHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Health)
	virtual void TakeDamage(float DamageAmount, TSubclassOf<UDamageType> DamageType) override;

	UFUNCTION(BlueprintCallable, Category = Health)
	void RegenerateHealth();

	UFUNCTION(BlueprintCallable, Category = Health)
	void SetMaxHealth(float NewHealth);

	UFUNCTION(BlueprintCallable, Category = Health)
	void SetRegenerationRate(float NewRegenerationRate);

	UFUNCTION(BlueprintCallable, Category = Health)
	void SetRegenRateInterval(float NewHealthRegenRateInterval);

	UFUNCTION(BlueprintCallable, Category = Health)
	void SetRegenRateDelay(float NewHealthRegenRateDelay);

	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealth() const { return CurrentHealth; }


protected:
	virtual void BeginPlay() override;

	FTimerHandle HealthRegenTimerHandle;

	float LastDamageTime;

	UPROPERTY(EditAnywhere, Category = Health)
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = Health)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = Health)
	float HealthRegenRate;

	UPROPERTY(EditAnywhere, Category = Health)
	float HealthRegenDelay = 3.0f;

	UPROPERTY(EditAnywhere, Category = Health)
	float HealthRegenInterval = 2.0f;
};
