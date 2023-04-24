// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassSmartObjectBehaviorDefinition.h"
#include "TNTGatherResourceBehaviorDefinition.generated.h"

class UMassEntityConfigAsset;
enum class ETNTResourceType : uint8;
/**
 * 
 */
UCLASS()
class MASSAI_API UTNTGatherResourceBehaviorDefinition : public USmartObjectMassBehaviorDefinition
{
	GENERATED_BODY()

public:
	/** This virtual method allows subclasses to configure the MassEntity based on their parameters (e.g. Add fragments) */
	virtual void Activate(FMassCommandBuffer& CommandBuffer,
	                      const FMassBehaviorEntityContext& EntityContext) const override;

	/** This virtual method allows subclasses to update the MassEntity on interaction deactivation (e.g. Remove fragments) */
	virtual void Deactivate(FMassCommandBuffer& CommandBuffer,
	                        const FMassBehaviorEntityContext& EntityContext) const override;

	UPROPERTY(EditDefaultsOnly, Category= SmartObject)
	int32 ResourceAmount = 1;


	UPROPERTY(EditDefaultsOnly, Category= SmartObject)
	TEnumAsByte<ETNTResourceType> ResourceType;

	UPROPERTY(EditDefaultsOnly, Category= SmartObject)
	UMassEntityConfigAsset* ItemConfig;
};
