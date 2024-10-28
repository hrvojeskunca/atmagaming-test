#pragma once

#include "TestStruct.generated.h"

USTRUCT(BlueprintType)
struct ATMAGAMING_API FTestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float BulletDamage;

	UPROPERTY(EditAnywhere)
	float BulletMaxSpeed;

	UPROPERTY(EditAnywhere)
	float BulletInitialSpeed;
};