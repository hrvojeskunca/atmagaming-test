// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class USphereComponent;
class UChildActorComponent;

UCLASS(Abstract)
class ATMAGAMING_API APawnBase : public APawn
{
	GENERATED_BODY()

public:

	APawnBase();

	virtual void Tick(float DeltaTime) override;

	UStaticMeshComponent* GetMesh() const;
	UChildActorComponent* GetWeaponAttachmentComponent() const;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TObjectPtr<UChildActorComponent> WeaponAttachmentComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	TObjectPtr<USphereComponent> CollisionComponent;

};
