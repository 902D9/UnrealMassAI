// Fill out your copyright notice in the Description page of Project Settings.


#include "TNTConstructBuilding.h"

#include "MassSmartObjectFragments.h"
#include "SmartObjectComponent.h"
#include "TNTAgentTrait.h"
#include "TNTBuildingSubsystem.h"
#include "SmartObjectSubsystem.h"
#include "Components/InstancedStaticMeshComponent.h"

UTNTConstructBuilding::UTNTConstructBuilding()
{
	bAutoRegisterWithProcessingPhases = true;
	ObservedType = FTNTConstructFloor::StaticStruct();
	Operation = EMassObservedOperation::Add;
}

void UTNTConstructBuilding::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// EntityQuery.ParallelForEachEntityChunk ???
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		const TArrayView<FTNTAgentFragment> RTSAgents = Context.GetMutableFragmentView<FTNTAgentFragment>();
		const TConstArrayView<FMassSmartObjectUserFragment> SOUsers = Context.GetFragmentView<
			FMassSmartObjectUserFragment>();
		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			FTNTAgentFragment& TNTAgent = RTSAgents[EntityIndex];
			const FMassSmartObjectUserFragment& SOUser = SOUsers[EntityIndex];

			if (const USmartObjectComponent* SmartObjectComponent = SmartObjectSubsystem->GetSmartObjectComponent(
				SOUser.InteractionHandle))
			{
				if (AActor* Actor = SmartObjectComponent->GetOwner())
				{
					// Essentially pick the correct ISM based on the floor level (Floor, Mid, Roof)
					UInstancedStaticMeshComponent* InstancedStaticMeshComp = Actor->FindComponentByClass<
						UInstancedStaticMeshComponent>();

					FTransform Transform;
					Transform.SetLocation(
						FVector(0, 0, IncrementHeight * InstancedStaticMeshComp->GetInstanceCount()) + Actor->
						GetActorLocation());
					Transform.SetRotation(FRotator(0.0, FMath::RandRange(0, 3) * 90.0, 0.0).Quaternion());
					InstancedStaticMeshComp->AddInstance(Transform, true);
				}

				TNTAgent.BuildingHandle = FSmartObjectHandle::Invalid;
				Context.Defer().RemoveTag<FTNTConstructFloor>(Context.GetEntity(EntityIndex));

				int* ResourceAmount = TNTAgent.Inventory.Find(ETNTResourceType::Rock);
				if (ResourceAmount)
				{
					*ResourceAmount -= 1;
				}
				ResourceAmount = TNTAgent.Inventory.Find(ETNTResourceType::Tree);
				if (ResourceAmount)
				{
					*ResourceAmount -= 1;
				}
			}
		}
	});
}


void UTNTConstructBuilding::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTNTAgentFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassSmartObjectUserFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.RegisterWithProcessor(*this); //5.1
}

void UTNTConstructBuilding::Initialize(UObject& Owner)
{
	Super::Initialize(Owner);

	SmartObjectSubsystem = UWorld::GetSubsystem<USmartObjectSubsystem>(Owner.GetWorld());
}
