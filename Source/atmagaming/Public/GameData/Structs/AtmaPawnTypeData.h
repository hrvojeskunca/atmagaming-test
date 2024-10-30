#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AtmaPawnTypeData.generated.h"

USTRUCT(BlueprintType)
struct ATMAGAMING_API FAtmaPawnTypeData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FString Description;

    UPROPERTY(EditAnywhere)
    float InitialSpeed;

    UPROPERTY(EditAnywhere)
    float MaxSpeed;

    UPROPERTY(EditAnywhere)
    float Acceleration;

    UPROPERTY(EditAnywhere)
    float Deceleration;

    UPROPERTY(EditAnywhere)
    int32 Health;

    UPROPERTY(EditAnywhere)
    float HealthRegenerationRate;

    UPROPERTY(EditAnywhere)
    float HealthRegenRateInterval;

    UPROPERTY(EditAnywhere)
    float HealthRegenRateDelay;
};
