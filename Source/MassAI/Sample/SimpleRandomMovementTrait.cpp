// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleRandomMovementTrait.h"

#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"

void USimpleRandomMovementTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	// Super::BuildTemplate(BuildContext, World);
	BuildContext.AddFragment<FSimpleMovementFragment>();
}

USimpleRandomMovementProcessor::USimpleRandomMovementProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)EProcessorExecutionFlags::All;
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void USimpleRandomMovementProcessor::ConfigureQueries()
{
	// Super::ConfigureQueries();
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FSimpleMovementFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.RegisterWithProcessor(*this); //5.1
}

void USimpleRandomMovementProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// Super::Execute(EntityManager, Context);
	// 遍历 EntityQuery 中的每个 EntityChunk
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		const TArrayView<FTransformFragment> TransformFragments = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FSimpleMovementFragment> SimpleMovementFragments = Context.GetMutableFragmentView<
			FSimpleMovementFragment>();
		const float WorldDeltaTime = Context.GetDeltaTimeSeconds();
		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			FTransform& Transform = TransformFragments[EntityIndex].GetMutableTransform();
			FVector& MoveTarget = SimpleMovementFragments[EntityIndex].Target;

			FVector CurLocation = Transform.GetLocation();
			FVector TargetVector = MoveTarget - CurLocation;
			if (TargetVector.Size() <= 20.f)
			{
				MoveTarget = FVector(FMath::RandRange(-1.f, 1.f) * 1000.f,
				                     FMath::RandRange(-1.f, 1.f) * 1000.f,
				                     CurLocation.Z);
			}
			else
			{
				Transform.SetLocation(CurLocation + TargetVector.GetSafeNormal() * 400.f * WorldDeltaTime);
			}
		}
	});
}
