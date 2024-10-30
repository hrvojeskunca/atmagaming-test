// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnBase.h"
#include "WeaponSystem/Weapons/AtmaWeaponBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Interfaces/HealthStatus.h"
#include "Components/Health/AtmaHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "GameData/Structs/AtmaPawnTypeData.h"
#include "UObject/Class.h"


APawnBase::APawnBase()
{

	PrimaryActorTick.bCanEverTick = false;

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
		CollisionComponent->InitSphereRadius(50.0f);
		RootComponent = CollisionComponent;
	}

	if (!MeshComponent)
	{
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
		MeshComponent->SetupAttachment(RootComponent);
	}

	if (!FloatingPawnMovementComponent)
	{
		FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
	}

	if (!WeaponAttachmentComponent)
	{
		WeaponAttachmentComponent = CreateDefaultSubobject<UChildActorComponent>("WeaponAttachmentComponent");
		WeaponAttachmentComponent->SetupAttachment(MeshComponent);
	}

	if (!HealthComponent)
	{
		HealthComponent = CreateDefaultSubobject<UAtmaHealthComponent>("HealthComponent");
		HealthComponent->bAutoActivate = true;
		HealthComponent->bEditableWhenInherited = true;
	}

	if (!WidgetComponent)
	{
		WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
		WidgetComponent->SetupAttachment(MeshComponent);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	}
}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();
}

void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
}

UStaticMeshComponent* APawnBase::GetMesh() const
{
	return MeshComponent;
}

UChildActorComponent* APawnBase::GetWeaponAttachmentComponent() const
{
	return WeaponAttachmentComponent;
}

void APawnBase::ApplyDamage(AActor* DamageActor, float DamageAmount, TSubclassOf<UDamageType> DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HealthComponent->GetClass()->ImplementsInterface(UHealthStatus::StaticClass()))
	{
		IHealthStatus* HealthStatusInterface = CastChecked<IHealthStatus>(HealthComponent);

		HealthStatusInterface->TakeDamage(DamageAmount, DamageType);
	}
}

void APawnBase::SetPawnData(EAtmaPawnType NewPawnType)
{
	UDataTable* AtmaPawnTypeDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DataTables/AtmaPawnTypeData"));
	if (AtmaPawnTypeDataTable)
	{
		FName PawnTypeName = StaticEnum<EAtmaPawnType>()->GetValueAsName(NewPawnType);

		static const FString ContextString(TEXT("AtmaPawnTypeContext"));
		FAtmaPawnTypeData* PawnTypeData = AtmaPawnTypeDataTable->FindRow<FAtmaPawnTypeData>(PawnTypeName, ContextString);

		if (PawnTypeData)
		{
			DefaultPawnSpeed = PawnTypeData->InitialSpeed;

			FloatingPawnMovementComponent->MaxSpeed = PawnTypeData->MaxSpeed;
			FloatingPawnMovementComponent->Acceleration = PawnTypeData->Acceleration;
			FloatingPawnMovementComponent->Deceleration = PawnTypeData->Deceleration;

			HealthComponent->SetMaxHealth(PawnTypeData->Health);
			HealthComponent->SetRegenerationRate(PawnTypeData->HealthRegenerationRate);
			HealthComponent->SetRegenRateInterval(PawnTypeData->HealthRegenRateInterval);
			HealthComponent->SetRegenRateDelay(PawnTypeData->HealthRegenRateDelay);
		}
	}
}
