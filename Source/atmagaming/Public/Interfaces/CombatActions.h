// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatActions.generated.h"

UINTERFACE(MinimalAPI)
class UCombatActions : public UInterface
{
	GENERATED_BODY()
};

class ATMAGAMING_API ICombatActions
{
	GENERATED_BODY()

public:
	virtual void Fire() = 0;
};
