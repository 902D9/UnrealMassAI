// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedRandomMovementProcessor.h"

#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassNavigationFragments.h"
#include "MassMovementFragments.h"

UAdvancedRandomMovementProcessor::UAdvancedRandomMovementProcessor()
{
	bAutoRegisterWithProcessingPhases = false;
	ExecutionFlags = (int32)EProcessorExecutionFlags::All;
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void UAdvancedRandomMovementProcessor::ConfigureQueries()
{
	// Super::ConfigureQueries();
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassMoveTargetFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddConstSharedRequirement<FMassMovementParameters>(EMassFragmentPresence::All);
	EntityQuery.RegisterWithProcessor(*this); //5.1
}

void UAdvancedRandomMovementProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// Super::Execute(EntityManager, Context);
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		const TConstArrayView<FTransformFragment> TransformFragments = Context.GetFragmentView<FTransformFragment>();
		const TArrayView<FMassMoveTargetFragment> MassMoveTargetFragments = Context.GetMutableFragmentView<
			FMassMoveTargetFragment>();
		const FMassMovementParameters& MovementParameters = Context.GetConstSharedFragment<FMassMovementParameters>();

		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			const FTransform& Transform = TransformFragments[EntityIndex].GetTransform();
			FMassMoveTargetFragment& MoveTarget = MassMoveTargetFragments[EntityIndex];

			FVector CurLocation = Transform.GetLocation();
			FVector TargetVector = MoveTarget.Center - CurLocation;
			TargetVector.Z = 0.f;
			MoveTarget.DistanceToGoal = TargetVector.Size();
			MoveTarget.Forward = TargetVector.GetSafeNormal();

			if (MoveTarget.DistanceToGoal <= 20.f || MoveTarget.Center == FVector::ZeroVector)
			{
				MoveTarget.Center = FVector(FMath::RandRange(-1.f, 1.f) * 1000.f,
				                            FMath::RandRange(-1.f, 1.f) * 1000.f,
				                            CurLocation.Z);
				MoveTarget.DistanceToGoal = (MoveTarget.Center - Transform.GetLocation()).Size();
				MoveTarget.Forward = (MoveTarget.Center - Transform.GetLocation()).GetSafeNormal();
				MoveTarget.DesiredSpeed = FMassInt16Real(MovementParameters.DefaultDesiredSpeed);
			}
		}
	});
}
