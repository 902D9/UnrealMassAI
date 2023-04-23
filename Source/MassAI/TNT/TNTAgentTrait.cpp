// Fill out your copyright notice in the Description page of Project Settings.


#include "TNTAgentTrait.h"

#include "MassEntitySubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "MassRepresentationFragments.h"
#include "TNTBuildingSubsystem.h"

void UTNTAgentTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	// Super::BuildTemplate(BuildContext, World);

	BuildContext.AddFragment<FTNTAgentFragment>();

	// find 5.1 useage from MassZoneGraphNavigationTrait
	FMassEntityManager& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
	const FConstSharedStruct AgentFragment = EntityManager.GetOrCreateConstSharedFragment(AgentParameters);
	BuildContext.AddConstSharedFragment(AgentFragment);

	BuildContext.AddTag<FTNTAgentTag>();
}

UTNTAgentInitializerProcessor::UTNTAgentInitializerProcessor()
{
	ObservedType = FTNTAgentFragment::StaticStruct();
	Operation = EMassObservedOperation::Add;
}

void UTNTAgentInitializerProcessor::ConfigureQueries()
{
	// Super::ConfigureQueries();
	EntityQuery.AddRequirement<FTNTAgentFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddConstSharedRequirement<FTNTAgentParameters>(EMassFragmentPresence::All);
	EntityQuery.AddTagRequirement<FTNTAgentTag>(EMassFragmentPresence::All);
	EntityQuery.AddRequirement<FMassRepresentationFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.RegisterWithProcessor(*this); //5.1
}

void UTNTAgentInitializerProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// Super::Execute(EntityManager, Context);
	BuildingSubsystem = GetWorld()->GetSubsystem<UTNTBuildingSubsystem>();
	for(int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++ EntityIndex)
	{
		BuildingSubsystem->AddAgent(Context.GetEntity(EntityIndex));
	}
}
