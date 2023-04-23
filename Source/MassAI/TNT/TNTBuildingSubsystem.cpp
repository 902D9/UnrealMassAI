// Fill out your copyright notice in the Description page of Project Settings.


#include "TNTBuildingSubsystem.h"

#include "MassEntitySubsystem.h"
#include "TNTItemTrait.h"

void UTNTBuildingSubsystem::AddResourceQueue(FSmartObjectHandle& SOHandle)
{
	if (QueueResources.Find(SOHandle) == INDEX_NONE)
	{
		QueueResources.Emplace(SOHandle);
	}
}

void UTNTBuildingSubsystem::AddAgent(const FMassEntityHandle& Entity)
{
	Agents.Emplace(Entity);
}

void UTNTBuildingSubsystem::AddBuilding(const FSmartObjectHandle& BuildingRequest, int32 Floors)
{
	QueueBuildings.Emplace(FTNTBuild(BuildingRequest, Floors));
}

bool UTNTBuildingSubsystem::ClaimFloor(FSmartObjectHandle& OutBuilding)
{
	bool bSuccess = false;
	if (QueueBuildings.Num() > 0)
	{
		FTNTBuild& Build = QueueBuildings[0];
		Build.FloorsNeeded--;
		OutBuilding = Build.BuildingRequest;
		bSuccess = true;
		if (Build.FloorsNeeded <= 0) // 不允许继续建造
		{
			QueueBuildings.RemoveAt(0);
		}
	}
	return bSuccess;
}

bool UTNTBuildingSubsystem::FindItem(const FVector& Location, float Radius, ETNTResourceType ResourceType,
                                     FMassEntityHandle& OutItemHandle)
{
	// UMassEntitySubsystem* EntitySubsystem = GetWorld()->GetSubsystem<UMassEntitySubsystem>();
	FMassEntityManager& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(*GetWorld());
	// 查找网格内最近的物品
	const TPair<FMassEntityHandle, float> ItemHandle = ItemGrid.FindNearestInRadius(
		Location, Radius,
		[this,&Location, &EntityManager](const FMassEntityHandle& EntityHandle)
		{
			if (!EntityManager.IsEntityValid(EntityHandle))
			{
				return 9999.f;
			}
			// 返回位置
			const FVector& OtherLocation = EntityManager.GetFragmentDataPtr<FTNTItemFragment>(EntityHandle)->OldLocation;
			const float Distance = FVector::Distance(OtherLocation, Location);
			return Distance;
		},
		[this,&ResourceType,&EntityManager](const FMassEntityHandle& EntityHandle)
		{
			if (!EntityManager.IsEntityValid(EntityHandle))
			{
				return true;
			}
			// 返回声明
			FTNTItemFragment& ItemFragment = EntityManager.GetFragmentDataChecked<FTNTItemFragment>(EntityHandle);
			return ItemFragment.bClaimed || ItemFragment.ItemType == ResourceType;
		});

	OutItemHandle = ItemHandle.Key;
	return EntityManager.IsEntityValid(ItemHandle.Key);
}

bool UTNTBuildingSubsystem::ClaimResource(FSmartObjectHandle& OutResourceHandle)
{
	bool bSuccess = false;
	if (QueueResources.Num() > 0)
	{
		bSuccess = true;
		OutResourceHandle = QueueResources[0];
		QueueResources.RemoveAt(0);
	}
	return bSuccess;
}
