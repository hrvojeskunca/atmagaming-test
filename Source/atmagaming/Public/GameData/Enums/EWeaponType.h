#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Projectile UMETA(DisplayName = "Projectile"),
    Hitscan UMETA(DisplayName = "Hitscan"),
};