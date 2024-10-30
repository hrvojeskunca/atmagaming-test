#pragma once

#include "CoreMinimal.h"
#include "AtmaPlayerDataMap.generated.h"

USTRUCT(BlueprintType)
struct ATMAGAMING_API FAtmaPlayerDataMap
{
    GENERATED_BODY()

    FAtmaPlayerDataMap()
    {
        PlayerValues.Add(TEXT("DefaultSpeed"), .7f);
        PlayerValues.Add(TEXT("MaxSpeed"), 1000.f);
        PlayerValues.Add(TEXT("Acceleration"), 250.f);
        PlayerValues.Add(TEXT("Deceleration"), 300.f);
        PlayerValues.Add(TEXT("Health"), 100.f);
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerData)
    TMap<FName, float> PlayerValues;
};
