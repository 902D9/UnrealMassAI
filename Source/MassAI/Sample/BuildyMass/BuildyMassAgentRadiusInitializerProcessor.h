// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassObserverProcessor.h"
#include "BuildyMassAgentRadiusInitializerProcessor.generated.h"

/**
 * 
 */
UCLASS()
class MASSAI_API UBuildyMassAgentRadiusInitializerProcessor : public UMassObserverProcessor
{
	GENERATED_BODY()

public:
	UBuildyMassAgentRadiusInitializerProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

private:
	FMassEntityQuery EntityQuery;
};
