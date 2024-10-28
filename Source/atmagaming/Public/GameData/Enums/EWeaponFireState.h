#pragma once

UENUM(BlueprintType)
enum class EWeaponFireState : uint8
{
    Ready UMETA(DisplayName = "Ready"),
    Cooldown UMETA(DisplayName = "Cooldown")
};