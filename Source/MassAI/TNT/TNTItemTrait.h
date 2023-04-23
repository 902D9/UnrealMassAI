// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "MassEntityTypes.h"
#include "MassRepresentationSubsystem.h"
#include "TNTAgentTrait.h"
#include "TNTBuildingSubsystem.h"
#include "TNTItemTrait.generated.h"

USTRUCT(BlueprintType)
struct FTNTItemFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY()
	TEnumAsByte<ETNTResourceType> ItemType;

	UPROPERTY()
	FVector OldLocation;

	UPROPERTY()
	bool bClaimed = false;
};

// 是否加入网格Tag
USTRUCT()
struct FTNTItemAddedToGrid : public FMassTag
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class MASSAI_API UTNTItemTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};

/**
 * 
 */
UCLASS()
class MASSAI_API UTNTItemProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:
	UTNTItemProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	virtual void Initialize(UObject& Owner) override;

private:
	FMassEntityQuery EntityQuery;

	UPROPERTY()
	UTNTBuildingSubsystem* BuildingSubsystem;

	UPROPERTY()
	UMassRepresentationSubsystem* RepresentationSubsystem;
};

/**
 * 
 */
UCLASS()
class MASSAI_API UTNTItemInitializerProcessor : public UMassObserverProcessor
{
	GENERATED_BODY()

public:
	UTNTItemInitializerProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	virtual void Initialize(UObject& Owner) override;

private:
	FMassEntityQuery EntityQuery;

	UPROPERTY()
	UTNTBuildingSubsystem* BuildingSubsystem;

	UPROPERTY()
	UMassRepresentationSubsystem* RepresentationSubsystem;
};
