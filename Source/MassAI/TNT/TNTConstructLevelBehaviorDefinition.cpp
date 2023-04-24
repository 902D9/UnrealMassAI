// Fill out your copyright notice in the Description page of Project Settings.


#include "TNTConstructLevelBehaviorDefinition.h"
#include "MassCommandBuffer.h"
#include "MassCommands.h"
#include "TNTConstructBuilding.h"
#include "MassSmartObjectFragments.h"

void UTNTConstructLevelBehaviorDefinition::Activate(FMassCommandBuffer& CommandBuffer,
                                                    const FMassBehaviorEntityContext& EntityContext) const
{
	Super::Activate(CommandBuffer, EntityContext);

	const FMassEntityHandle& Entity = EntityContext.EntityView.GetEntity();
	// FMassSmartObjectUserFragment& SOUser = EntityContext.EntityView.GetFragmentData<FMassSmartObjectUserFragment>();
	// CommandBuffer.PushCommand(FCommandAddTag(EntityContext.EntityView.GetEntity(), FRTSConstructFloor::StaticStruct())); // 5.0
	CommandBuffer.PushCommand<FMassCommandAddTag<FTNTConstructFloor>>(Entity); // 5.1
}

void UTNTConstructLevelBehaviorDefinition::Deactivate(FMassCommandBuffer& CommandBuffer,
                                                      const FMassBehaviorEntityContext& EntityContext) const
{
	Super::Deactivate(CommandBuffer, EntityContext);
}
