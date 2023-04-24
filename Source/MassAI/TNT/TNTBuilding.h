// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmartObjectComponent.h"
#include "GameFramework/Actor.h"
#include "TNTBuilding.generated.h"

UCLASS()
class MASSAI_API ATNTBuilding : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATNTBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USmartObjectComponent* SmartObjectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Floors = 1;
};
