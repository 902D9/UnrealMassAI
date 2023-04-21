// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildyMassBuilderTrait.h"

#include "MassEntityTemplateRegistry.h"

void UBuildyMassBuilderTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	// Super::BuildTemplate(BuildContext, World);
	BuildContext.AddFragment<FBuildyMassBuilderStateFragment>();
	// todo add more data
	// BuildContext.AddFragment<FBuildyMassBuilderFragment>();
	BuildContext.AddFragment<FBuildyMassBuilderTag>();
}
