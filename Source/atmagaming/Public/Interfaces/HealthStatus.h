// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthStatus.generated.h"

UINTERFACE(MinimalAPI)
class UHealthStatus : public UInterface
{
	GENERATED_BODY()
};


class ATMAGAMING_API IHealthStatus
{
	GENERATED_BODY()

public:
	virtual void TakeDamage(float DamageAmount, TSubclassOf<UDamageType> DamageType) = 0;
};
