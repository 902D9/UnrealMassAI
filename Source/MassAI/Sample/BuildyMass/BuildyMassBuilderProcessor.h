// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildyMassGridSubsystem.h"
#include "MassProcessor.h"
#include "BuildyMassBuilderProcessor.generated.h"

/**
typedef FBuildyMassGridCellContent BuildyMassGrid[3][3];

USTRUCT()
struct BUILDYMASS_API FBuildyMassMovemnetStateFragment : public FMassFragment
{
	GENERATED_BODY()

FVector TargetLocation;
	uint32 CachedGridX;
	uint32 CachedGridY;
	UBuildyMassGridSubsystem::BuildyMassSubGrid CachedGrid;
	bool bStartGoing;
};
*/


/**
 * 
 */
UCLASS()
class MASSAI_API UBuildyMassBuilderProcessor : public UMassProcessor
{
	GENERATED_BODY()
public:
	UBuildyMassBuilderProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

private:
	UPROPERTY()
	TObjectPtr<UBuildyMassGridSubsystem> GridSubsystem;
	// TObjectPtr<UBuildyMassBuildingSubsystem> BuildingSubsystem;
};
