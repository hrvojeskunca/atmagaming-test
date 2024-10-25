#pragma once

#include "CoreMinimal.h"
#include "AtmaPlayerPawnData.generated.h"

USTRUCT(BlueprintType)
struct FAtmaPlayerPawnData
{
	GENERATED_BODY()

	FAtmaPlayerPawnData()
	{
		PlayerValues.Add(FName("DefaultSpeed"), .7f);
		PlayerValues.Add(FName("MaxSpeed"), 10000.f);
		PlayerValues.Add(FName("Acceleration"), 1000.f);
		PlayerValues.Add(FName("Deceleration"), 3000.f);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	TMap<FName, float> PlayerValues;
};