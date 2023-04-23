// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "MassEntityTypes.h"
#include "MassObserverProcessor.h"
#include "SmartObjectTypes.h"
#include "TNTAgentTrait.generated.h"

class UTNTBuildingSubsystem;

UENUM(BlueprintType)
enum class ETNTResourceType : uint8
{
	Tree,
	Rock
};

USTRUCT(BlueprintType)
struct FTNTAgentFragment : public FMassFragment
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<ETNTResourceType>, int> Inventory;

	UPROPERTY()
	FSmartObjectHandle BuildingHandle;

	UPROPERTY()
	FSmartObjectHandle ResourceHandle;

	UPROPERTY()
	TArray<FMassEntityHandle> QueuedItems;
};

USTRUCT()
struct MASSAI_API FTNTAgentParameters : public FMassSharedFragment
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<TEnumAsByte<ETNTResourceType>, int> DefaultRequiredResources;
};

USTRUCT()
struct FTNTAgentTag : public FMassTag
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class MASSAI_API UTNTAgentTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;

	UPROPERTY(EditAnywhere)
	FTNTAgentParameters AgentParameters;
};


/**
 * 
 */
UCLASS()
class MASSAI_API UTNTAgentInitializerProcessor : public UMassObserverProcessor
{
	GENERATED_BODY()

public:
	UTNTAgentInitializerProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	
	TObjectPtr<UTNTBuildingSubsystem> BuildingSubsystem;
	TObjectPtr<USmartObjectSubsystem> SmartObjectSubsystem;

private:
	FMassEntityQuery EntityQuery;
};
