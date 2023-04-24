// // Fill out your copyright notice in the Description page of Project Settings.
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "MassCommonFragments.h"
// #include "MassEntitySubsystem.h"
// #include "MassStateTreeTypes.h"
// #include "SmartObjectSubsystem.h"
// #include "TNTRequiredMaterialsEvaluator.generated.h"
//
// class UTNTBuildingSubsystem;
// struct FTNTAgentFragment;
//
// USTRUCT()
// struct MASSAI_API FTNTRequiredMaterialsEvaluatorInstanceData
// {
// 	GENERATED_BODY()
//
// 	UPROPERTY(EditAnywhere, Category = Output)
// 	FSmartObjectRequestFilter Filter;
//
// 	UPROPERTY(EditAnywhere, Category = Output)
// 	FSmartObjectHandle SmartObjectHandle;
//
// 	UPROPERTY(EditAnywhere, Category = Output)
// 	FMassEntityHandle ItemHandle;
//
// 	UPROPERTY(EditAnywhere, Category = Output)
// 	bool bFoundSmartObject = false;
//
// 	UPROPERTY(EditAnywhere, Category = Output)
// 	bool bFoundItemHandle = false;
// };
//
// /**
//  * 
//  */
// USTRUCT()
// struct MASSAI_API FTNTRequiredMaterialsEvaluator : public FMassStateTreeEvaluatorBase
// {
// 	GENERATED_BODY()
//
// 	FTNTRequiredMaterialsEvaluator();
//
// 	// virtual void Evaluate(FStateTreeExecutionContext& Context, const EStateTreeEvaluationType EvalType, const float DeltaTime) const override; // 5.0
// 	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override; // 5.1
// 	virtual bool Link(FStateTreeLinker& Linker) override;
// 	virtual const UStruct* GetInstanceDataType() const override { return FTNTRequiredMaterialsEvaluatorInstanceData::StaticStruct(); }
//
// 	TStateTreeExternalDataHandle<FTNTAgentFragment> TNTAgentHandle;
// 	TStateTreeExternalDataHandle<USmartObjectSubsystem> SmartObjectSubsystemHandle;
// 	TStateTreeExternalDataHandle<UMassEntitySubsystem> EntitySubsystemHandle;
// 	TStateTreeExternalDataHandle<FTransformFragment> TransformHandle;
// 	TStateTreeExternalDataHandle<UTNTBuildingSubsystem> BuildingSubsystemHandle;
// 	
// 	// TStateTreeInstanceDataPropertyHandle<bool> FoundSmartObjectHandle;
// 	// TStateTreeInstanceDataPropertyHandle<FSmartObjectRequestFilter> FilterHandle;
// 	// TStateTreeInstanceDataPropertyHandle<bool> FoundItemHandle;
// 	// TStateTreeInstanceDataPropertyHandle<FSmartObjectHandle> SmartObjectHandle;
// 	// TStateTreeInstanceDataPropertyHandle<FMassEntityHandle> ItemHandle;
// 	
// 	TStateTreeExternalDataHandle<bool> FoundSmartObjectHandle;
// 	TStateTreeExternalDataHandle<FSmartObjectRequestFilter> FilterHandle;
// 	TStateTreeExternalDataHandle<bool> FoundItemHandle;
// 	TStateTreeExternalDataHandle<FSmartObjectHandle> SmartObjectHandle;
// 	TStateTreeExternalDataHandle<FMassEntityHandle> ItemHandle;
// };
