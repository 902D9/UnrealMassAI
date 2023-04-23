// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmartObjectTypes.h"
#include "Subsystems/WorldSubsystem.h"
#include "TNTAgentTrait.h"
#include "Spatial/PointHashGrid3.h"
#include "TNTBuildingSubsystem.generated.h"

// 哈希网格查询点
typedef UE::Geometry::TPointHashGrid3<FMassEntityHandle, Chaos::FReal> ItemHashGrid3D;

// 处理建造的请求和楼层
USTRUCT()
struct MASSAI_API FTNTBuild
{
	GENERATED_BODY()

	UPROPERTY()
	FSmartObjectHandle BuildingRequest;

	UPROPERTY()
	int32 FloorsNeeded = 1;

	FTNTBuild()
	{
	};

	FTNTBuild(const FSmartObjectHandle& BuildingRequest, int32 FloorsNeeded)
	{
		this->BuildingRequest = BuildingRequest;
		this->FloorsNeeded = FloorsNeeded;
	};

	bool operator==(const FTNTBuild& Other) const
	{
		return BuildingRequest == Other.BuildingRequest;
	}
};

/**
 * 
 */
UCLASS()
class MASSAI_API UTNTBuildingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// 添加资源到队列
	UFUNCTION(BlueprintCallable)
	void AddResourceQueue(FSmartObjectHandle& SOHandle);

	// 添加 Mass 代理
	UFUNCTION()
	void AddAgent(const FMassEntityHandle& Entity);

	// 将建筑添加到子系统，用实体构建
	UFUNCTION(BlueprintCallable)
	void AddBuilding(const FSmartObjectHandle& BuildingRequest, int32 Floors = 1);

	// 需要建造到哪个楼层
	UFUNCTION()
	bool ClaimFloor(FSmartObjectHandle& OutBuilding);

	// 找到资源
	bool FindItem(const FVector& Location, float Radius, ETNTResourceType ResourceType,
	              FMassEntityHandle& OutItemHandle);

	// 获取要建造的队列
	int32 GetQueueBuildings() const { return QueueBuildings.Num(); };

	// 获取队列的资源
	void GetQueueResources(TArray<FSmartObjectHandle>& OutQueueResources) const { OutQueueResources = QueueResources; }

	// 声明资源
	bool ClaimResource(FSmartObjectHandle& OutResourceHandle);

	UPROPERTY()
	FMassEntityHandle Agent;

	TArray<FTNTBuild> QueueBuildings;

	TArray<FMassEntityHandle> Agents;

	TArray<FSmartObjectHandle> QueueResources;

	ItemHashGrid3D ItemGrid = ItemHashGrid3D(500.f, FMassEntityHandle());
};
