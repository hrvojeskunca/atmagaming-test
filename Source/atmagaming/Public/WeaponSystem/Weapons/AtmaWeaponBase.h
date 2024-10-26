// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AtmaWeaponBase.generated.h"

UCLASS()
class ATMAGAMING_API AAtmaWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAtmaWeaponBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;

private:
	AActor* OwnerPawn;

};
