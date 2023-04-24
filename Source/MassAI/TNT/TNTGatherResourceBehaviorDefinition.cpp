// Fill out your copyright notice in the Description page of Project Settings.


#include "TNTGatherResourceBehaviorDefinition.h"

#include "MassCommonFragments.h"
#include "MassEntityConfigAsset.h"
#include "MassEntitySubsystem.h"
#include "MassSmartObjectFragments.h"
#include "MassSpawnerSubsystem.h"
#include "SmartObjectComponent.h"
#include "SmartObjectSubsystem.h"
#include "TNTAgentTrait.h"
#include "TNTItemTrait.h"
#include "Kismet/GameplayStatics.h"

void UTNTGatherResourceBehaviorDefinition::Activate(FMassCommandBuffer& CommandBuffer,
                                                    const FMassBehaviorEntityContext& EntityContext) const
{
	Super::Activate(CommandBuffer, EntityContext);

	FTNTAgentFragment& AgentFragment = EntityContext.EntityView.GetFragmentData<FTNTAgentFragment>();

	// Invalidate resource handle when complete
	// AgentFragment.ResourceHandle.Reset(); // 5.0
	AgentFragment.ResourceHandle.Invalidate(); // 5.1
}

void UTNTGatherResourceBehaviorDefinition::Deactivate(FMassCommandBuffer& CommandBuffer,
                                                      const FMassBehaviorEntityContext& EntityContext) const
{
	Super::Deactivate(CommandBuffer, EntityContext);


	if (const UWorld* World = EntityContext.SmartObjectSubsystem.GetWorld())
	{
		UMassSpawnerSubsystem* SpawnerSubsystem = UWorld::GetSubsystem<UMassSpawnerSubsystem>(World);

		// 根据配置文件生成实体
		TArray<FMassEntityHandle> Items;
		// 5.0
		// APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(EntityContext.SmartObjectSubsystem.GetWorld(), 0);
		// const FMassEntityTemplate* EntityTemplate = ItemConfig->GetConfig().GetOrCreateEntityTemplate(
		// 	*PlayerPawn, *ItemConfig); 
		const FMassEntityTemplate& EntityTemplate = ItemConfig->GetConfig().GetOrCreateEntityTemplate(
			*World, *ItemConfig); // 5.1
		// SpawnerSubsystem->SpawnEntities(*EntityTemplate, 4, Items); // 5.0 
		SpawnerSubsystem->SpawnEntities(EntityTemplate, 4, Items); // 5.1

		for (const FMassEntityHandle& ItemHandle : Items)
		{
			const FVector& SpawnLocation = EntityContext.EntityView.GetFragmentDataPtr<FTransformFragment>()->
			                                             GetTransform().GetLocation();
			FTNTItemFragment ItemFragment;
			ItemFragment.ItemType = ResourceType;
			ItemFragment.OldLocation = SpawnLocation;
			// 5.0
			// CommandBuffer.PushCommand(
			// 	FMassCommandAddFragmentInstances(ItemHandle, FConstStructView::Make(ItemFragment)));

			// CommandBuffer.PushCommand<FMassCommandAddFragmentInstances>(ItemHandle,  FConstStructView::Make(ItemFragment));
			CommandBuffer.PushCommand<FMassCommandAddFragmentInstances>(ItemHandle, ItemFragment); // 5.1 
		}

		// 销毁资源 Actor
		// const FMassSmartObjectUserFragment* SOUser = EntityContext.EntityView.GetFragmentData<
		// 	FMassSmartObjectUserFragment>(); // 5.0
		const FMassSmartObjectUserFragment& SOUser = EntityContext.EntityView.GetFragmentData<
			FMassSmartObjectUserFragment>();
		// (5.0) SOUser.ClaimHandle 
		if (USmartObjectComponent* SOComp = EntityContext.SmartObjectSubsystem.GetSmartObjectComponent(
			SOUser.InteractionHandle))
		{
			// 5.0
			// CommandBuffer.PushCommand(FDeferredCommand([SOComp, EntityContext](UMassEntitySubsystem& System)
			// {
			// 	SOComp->GetOwner()->Destroy();
			// }));

			// 5.1 待测
			// CommandBuffer.PushCommand<FMassDeferredDestroyCommand>([SOComp, EntityContext](UMassEntitySubsystem& System)
			// {
			// 	SOComp->GetOwner()->Destroy();
			// });

			SOComp->GetOwner()->Destroy();
		}
	}
}
