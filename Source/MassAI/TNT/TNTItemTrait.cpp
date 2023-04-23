// Fill out your copyright notice in the Description page of Project Settings.


#include "TNTItemTrait.h"

#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "MassRepresentationFragments.h"

void UTNTItemTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment<FTNTItemFragment>();
}

UTNTItemProcessor::UTNTItemProcessor()
{
}

void UTNTItemProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTNTItemFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddTagRequirement<FTNTItemAddedToGrid>(EMassFragmentPresence::All);
	EntityQuery.RegisterWithProcessor(*this); //5.1
}

void UTNTItemProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// EntityQuery.ParallelForEachEntityChunk ???
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		const TConstArrayView<FTransformFragment> TransformFragments = Context.GetFragmentView<FTransformFragment>();
		const TArrayView<FTNTItemFragment> ItemFragments = Context.GetMutableFragmentView<FTNTItemFragment>();
		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			FTNTItemFragment& Item = ItemFragments[EntityIndex];
			const FVector& Location = TransformFragments[EntityIndex].GetTransform().GetLocation();
			BuildingSubsystem->ItemGrid.UpdatePoint(Context.GetEntity(EntityIndex), Item.OldLocation, Location);
			Item.OldLocation = Location;
		}
	});
}

void UTNTItemProcessor::Initialize(UObject& Owner)
{
	// Super::Initialize(Owner);
	BuildingSubsystem = GetWorld()->GetSubsystem<UTNTBuildingSubsystem>();
}

UTNTItemInitializerProcessor::UTNTItemInitializerProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ObservedType = FTransformFragment::StaticStruct();
	Operation = EMassObservedOperation::Add;
}

void UTNTItemInitializerProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTNTItemFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassRepresentationFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassRepresentationLODFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.RegisterWithProcessor(*this); //5.1
}

void UTNTItemInitializerProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		const TArrayView<FTransformFragment> TransformFragments = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FTNTItemFragment> ItemFragments = Context.GetMutableFragmentView<FTNTItemFragment>();
		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			FTNTItemFragment& Item = ItemFragments[EntityIndex];
			FTransform& Transform = TransformFragments[EntityIndex].GetMutableTransform();

			if (Transform.GetLocation() == FVector::Zero())
			{
				Item.OldLocation.X += FMath::FRandRange(-100.f, 100.f);
				Item.OldLocation.Y += FMath::FRandRange(-100.f, 100.f);
				Transform.SetLocation(Item.OldLocation);
			}
			BuildingSubsystem->ItemGrid.InsertPoint(Context.GetEntity(EntityIndex), Item.OldLocation);
			Context.Defer().AddTag<FTNTItemAddedToGrid>(Context.GetEntity(EntityIndex));
		}
	});
}

void UTNTItemInitializerProcessor::Initialize(UObject& Owner)
{
	// Super::Initialize(Owner);
	BuildingSubsystem = GetWorld()->GetSubsystem<UTNTBuildingSubsystem>();
}
