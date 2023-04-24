// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "TNTRequiredMaterialsEvaluator.h"
// #include "MassAI/TNT/TNTAgentTrait.h"
// #include "MassAI/TNT/TNTBuildingSubsystem.h"
// #include "MassSmartObjectBehaviorDefinition.h"
// #include "SmartObjectSubsystem.h"
// #include "StateTreeExecutionContext.h"
// #include "StateTreeLinker.h"
// #include "DSP/PassiveFilter.h"
// #include "MassAI/TNT/TNTItemTrait.h"
//
// FTNTRequiredMaterialsEvaluator::FTNTRequiredMaterialsEvaluator()
// {
// }
//
// void FTNTRequiredMaterialsEvaluator::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
// {
// 	// FMassStateTreeEvaluatorBase::Tick(Context, DeltaTime);
// 	// todo 不在这实现？
//
// 	FTNTAgentFragment& TNTAgent = Context.GetExternalData(TNTAgentHandle);
// 	UMassEntitySubsystem& EntitySubsystem = Context.GetExternalData(EntitySubsystemHandle);
// 	UTNTBuildingSubsystem& BuildingSubsystem = Context.GetExternalData(BuildingSubsystemHandle);
// 	const FVector& Location = Context.GetExternalData(TransformHandle).GetTransform().GetLocation();
//
// 	// FSmartObjectRequestFilter& Filter = Context.GetInstanceData(FilterHandle);
// 	// bool& bFoundSmartObject = Context.GetInstanceData(FoundSmartObjectHandle);
// 	// bool& bFoundItemHandle = Context.GetInstanceData(FoundItemHandle);
// 	// FSmartObjectHandle& SOHandle = Context.GetInstanceData(SmartObjectHandle);
// 	// FMassEntityHandle& EntityHandle = Context.GetInstanceData(ItemHandle);
//
// 	FSmartObjectRequestFilter& Filter = Context.GetExternalData(FilterHandle);
// 	bool& bFoundSmartObject = Context.GetExternalData(FoundSmartObjectHandle);
// 	bool& bFoundItemHandle = Context.GetExternalData(FoundItemHandle);
// 	FSmartObjectHandle& SOHandle = Context.GetExternalData(SmartObjectHandle);
// 	FMassEntityHandle& EntityHandle = Context.GetExternalData(ItemHandle);
//
// 	bFoundSmartObject = false;
// 	bFoundItemHandle = false;
//
// 	// Filter.BehaviorDefinitionClass = USmartObjectMassBehaviorDefinition::StaticClass();
// 	Filter.BehaviorDefinitionClasses = {USmartObjectMassBehaviorDefinition::StaticClass()};
//
// 	FSmartObjectRequest Request;
// 	Request.QueryBox = FBox::BuildAABB(Location, FVector(5000.0f));
//
// 	FGameplayTagQueryExpression Query;
// 	Query.AllTagsMatch();
//
// 	// We are currently gathering resources
// 	if (!EntitySubsystem.GetEntityManager().IsEntityValid(EntityHandle) && TNTAgent.QueuedItems.Num() > 0)
// 	{
// 		EntityHandle = TNTAgent.QueuedItems.Pop();
// 		if (EntitySubsystem.GetEntityManager().IsEntityValid(EntityHandle))
// 		{
// 			bFoundItemHandle = true;
// 			FTNTItemFragment* ItemFragment = EntitySubsystem.GetEntityManager().GetFragmentDataPtr<FTNTItemFragment>(
// 				EntityHandle);
// 			if (ItemFragment)
// 			{
// 				ItemFragment->bClaimed = true;
// 			}
// 			return;
// 		}
// 	}
//
// 	// Check whether agent is waiting for a command
// 	if (TNTAgent.QueuedItems.Num() <= 0 && !TNTAgent.BuildingHandle.IsValid())
// 	{
// 		// Before calculating items existence, we need to see if a building needs building
// 		if (BuildingSubsystem.GetQueuedBuildings() > 0)
// 		{
// 			// Before giving commands, we need to make sure the item(s) are available
// 			TArray<FMassEntityHandle> ItemHandles;
// 			ItemHandles.AddUninitialized(2);
//
// 			if (BuildingSubsystem.FindItem(Location, 5000.f, ETNTResourceType::Rock, ItemHandles[0]))
// 			{
// 				if (BuildingSubsystem.FindItem(Location, 5000.f, ETNTResourceType::Tree, ItemHandles[1]))
// 				{
// 					bFoundItemHandle = true;
// 					// Since they are available, we can claim/give the agent the handles to fetch them
// 					BuildingSubsystem.ClaimFloor(TNTAgent.BuildingHandle);
//
// 					TNTAgent.QueuedItems.Append(ItemHandles);
// 					EntityHandle = TNTAgent.QueuedItems.Pop();
//
// 					// We need to claim both because then its possible that another agent also 'wants' the item on the ground
// 					for (const FMassEntityHandle& Item : ItemHandles)
// 					{
// 						if (FTNTItemFragment* ItemFragment = EntitySubsystem.GetEntityManager().GetFragmentDataPtr<
// 							FTNTItemFragment>(Item))
// 						{
// 							ItemFragment->bClaimed = true;
// 						}
// 					}
//
// 					return;
// 				}
// 			}
// 		}
// 	}
//
// 	// We have finished collecting items and should head back to our building
// 	if (TNTAgent.BuildingHandle.IsValid() && TNTAgent.QueuedItems.Num() == 0)
// 	{
// 		bFoundSmartObject = true;
// 		SOHandle = TNTAgent.BuildingHandle;
// 		return;
// 	}
//
// 	// We dont have the resources/dont have a floor to build, so check if there are queued resources to chop
// 	if (BuildingSubsystem.GetNumQueuedResources() > 0 && !TNTAgent.ResourceHandle.IsValid())
// 	{
// 		// We have queued resources to chop, so we should try to chop one
// 		FSmartObjectHandle ResourceHandle;
// 		bFoundSmartObject = true;
// 		BuildingSubsystem.ClaimResource(ResourceHandle);
// 		TNTAgent.ResourceHandle = ResourceHandle;
// 		SOHandle = ResourceHandle;
// 	}
// }
//
// bool FTNTRequiredMaterialsEvaluator::Link(FStateTreeLinker& Linker)
// {
// 	Linker.LinkExternalData(TNTAgentHandle);
// 	Linker.LinkExternalData(SmartObjectSubsystemHandle);
// 	Linker.LinkExternalData(TransformHandle);
// 	Linker.LinkExternalData(EntitySubsystemHandle);
// 	Linker.LinkExternalData(BuildingSubsystemHandle);
//
// 	// Linker.LinkInstanceDataProperty(FoundSmartObjectHandle, STATETREE_INSTANCEDATA_PROPERTY(FTNTRequiredMaterialsEvaluatorInstanceData, bFoundSmartObject));
// 	// Linker.LinkInstanceDataProperty(FilterHandle, STATETREE_INSTANCEDATA_PROPERTY(FTNTRequiredMaterialsEvaluatorInstanceData, Audio::Filter));
// 	// Linker.LinkInstanceDataProperty(FoundItemHandle, STATETREE_INSTANCEDATA_PROPERTY(FTNTRequiredMaterialsEvaluatorInstanceData, bFoundItemHandle));
// 	// Linker.LinkInstanceDataProperty(SmartObjectHandle, STATETREE_INSTANCEDATA_PROPERTY(FTNTRequiredMaterialsEvaluatorInstanceData, SmartObjectHandle));
// 	// Linker.LinkInstanceDataProperty(ItemHandle, STATETREE_INSTANCEDATA_PROPERTY(FTNTRequiredMaterialsEvaluatorInstanceData, ItemHandle));
//
// 	// Linker.LinkExternalData(FoundSmartObjectHandle);
// 	// Linker.LinkExternalData(FilterHandle);
// 	// Linker.LinkExternalData(FoundItemHandle);
// 	// Linker.LinkExternalData(SmartObjectHandle);
// 	// Linker.LinkExternalData(ItemHandle);
//
// 	// Linker.LinkExternalData(FoundSmartObjectHandle, FTNTRequiredMaterialsEvaluatorInstanceData::StaticStruct(),
// 	//                         EStateTreeExternalDataRequirement::Required);
// 	// Linker.LinkInstanceDataProperty(FilterHandle, STATETREE_INSTANCEDATA_PROPERTY(FTNTRequiredMaterialsEvaluatorInstanceData, Audio::Filter));
// 	// Linker.LinkInstanceDataProperty(FoundItemHandle, STATETREE_INSTANCEDATA_PROPERTY(FTNTRequiredMaterialsEvaluatorInstanceData, bFoundItemHandle));
// 	// Linker.LinkInstanceDataProperty(SmartObjectHandle, STATETREE_INSTANCEDATA_PROPERTY(FTNTRequiredMaterialsEvaluatorInstanceData, SmartObjectHandle));
// 	// Linker.LinkInstanceDataProperty(ItemHandle, STATETREE_INSTANCEDATA_PROPERTY(FTNTRequiredMaterialsEvaluatorInstanceData, ItemHandle));
//
// 	return true;
// }
