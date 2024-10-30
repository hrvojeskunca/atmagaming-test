#pragma once

UENUM(BlueprintType)
enum class EAtmaPawnType : uint8
{
    Default UMETA(DisplayName = "Default"),
    Player_0 UMETA(DisplayName = "Player_0"),
    Enemy_0 UMETA(DisplayName = "Enemy_0"),
    Neutral_0 UMETA(DisplayName = "Neutral_0")
};
