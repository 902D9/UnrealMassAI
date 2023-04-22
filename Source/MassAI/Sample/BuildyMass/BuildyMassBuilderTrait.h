// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "MassEntityTypes.h"
#include "BuildyMassBuilderTrait.generated.h"

USTRUCT()
struct FBuildyMassBuilderStateFragment : public FMassFragment
{
	GENERATED_BODY()

	// todo add more data
	// UPROPERTY()
	// EBuildyMassBuilderState CurrentState;
	// UPROPERTY()
	// bool bArrived;
};

USTRUCT()
struct FBuildyMassBuilderTag : public FMassTag
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class MASSAI_API UBuildyMassBuilderTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
	
};
