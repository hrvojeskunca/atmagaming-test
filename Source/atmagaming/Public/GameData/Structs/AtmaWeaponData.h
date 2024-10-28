#pragma once

#include "CoreMinimal.h"
#include "AtmaWeaponData.generated.h"

USTRUCT(BlueprintType)
struct ATMAGAMING_API FAtmaWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    float BulletInitialSpeed;

    UPROPERTY(EditAnywhere)
    float BulletMaxSpeed;

    UPROPERTY(EditAnywhere)
    float BulletDamage;
};