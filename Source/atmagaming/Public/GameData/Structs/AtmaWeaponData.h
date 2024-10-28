#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameData/Enums/EWeaponType.h"
#include "AtmaWeaponData.generated.h"

USTRUCT(BlueprintType)
struct ATMAGAMING_API FAtmaWeaponData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere)
    float WeaponCooldown;

    UPROPERTY(EditAnywhere)
    float WeaponDamage;

    UPROPERTY(EditAnywhere)
    float BulletMaxSpeed;

    UPROPERTY(EditAnywhere)
    float BulletInitialSpeed;
};