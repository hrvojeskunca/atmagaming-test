// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

UCLASS(Abstract)
class ATMAGAMING_API APawnBase : public APawn
{
	GENERATED_BODY()

public:

	APawnBase();

	UStaticMeshComponent* GetMesh() const;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;

};
