// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatStatus.generated.h"

UINTERFACE(MinimalAPI)
class UCombatStatus : public UInterface
{
	GENERATED_BODY()
};

class ATMAGAMING_API ICombatStatus
{
	GENERATED_BODY()

public:
	virtual void ApplyDamage(AActor* DamageActor, float DamageAmount, TSubclassOf<UDamageType> DamageType, class AController* InstigatedBy, AActor* DamageCauser) = 0;
};
