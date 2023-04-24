// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassSmartObjectBehaviorDefinition.h"
#include "TNTConstructLevelBehaviorDefinition.generated.h"

/**
 * 
 */
UCLASS()
class MASSAI_API UTNTConstructLevelBehaviorDefinition : public USmartObjectMassBehaviorDefinition
{
	GENERATED_BODY()

public:
	virtual void Activate(FMassCommandBuffer& CommandBuffer,
	                      const FMassBehaviorEntityContext& EntityContext) const override;

	virtual void Deactivate(FMassCommandBuffer& CommandBuffer,
	                        const FMassBehaviorEntityContext& EntityContext) const override;
};
