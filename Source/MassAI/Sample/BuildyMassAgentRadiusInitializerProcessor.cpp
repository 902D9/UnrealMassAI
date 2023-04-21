// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildyMassAgentRadiusInitializerProcessor.h"

#include "BuildyMassBuilderTrait.h"
#include "MassCommonFragments.h"

UBuildyMassAgentRadiusInitializerProcessor::UBuildyMassAgentRadiusInitializerProcessor()
{
	ObservedType = FAgentRadiusFragment::StaticStruct();
	Operation = EMassObservedOperation::Add;
}

void UBuildyMassAgentRadiusInitializerProcessor::ConfigureQueries()
{
	// Super::ConfigureQueries();
	EntityQuery.AddRequirement<FAgentRadiusFragment>(EMassFragmentAccess::ReadWrite);
	// 过滤 避免筛选出全部的实体
	EntityQuery.AddTagRequirement<FBuildyMassBuilderTag>(EMassFragmentPresence::All);
	EntityQuery.RegisterWithProcessor(*this); //5.1
}

void UBuildyMassAgentRadiusInitializerProcessor::Execute(FMassEntityManager& EntityManager,
                                                         FMassExecutionContext& Context)
{
	// Super::Execute(EntityManager, Context);
	EntityQuery.ForEachEntityChunk(EntityManager, Context, ([this](FMassExecutionContext& Context)
	{
		const TArrayView<FAgentRadiusFragment> AgentRadiusFragments = Context.GetMutableFragmentView<
			FAgentRadiusFragment>();
		static uint32 CurrentId = 0;
		for (FAgentRadiusFragment& AgentRadiusFragment : AgentRadiusFragments)
		{
			AgentRadiusFragment.Radius = 20.f;
		}
	}));
}
