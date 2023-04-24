// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassObserverProcessor.h"
#include "TNTConstructBuilding.generated.h"

class UTNTBuildingSubsystem;
class USmartObjectSubsystem;

USTRUCT()
struct MASSAI_API FTNTConstructFloor : public FMassTag
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class MASSAI_API UTNTConstructBuilding : public UMassObserverProcessor
{
	GENERATED_BODY()

	UTNTConstructBuilding();

	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	virtual void ConfigureQueries() override;
	virtual void Initialize(UObject& Owner) override;

	TObjectPtr<UTNTBuildingSubsystem> TNTBuildingSubsystem;
	TObjectPtr<USmartObjectSubsystem> SmartObjectSubsystem;

	// 建造高度
	float IncrementHeight = 100.f;

	FMassEntityQuery EntityQuery;
};
