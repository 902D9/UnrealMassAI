// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TNTResource.generated.h"

UCLASS()
class MASSAI_API ATNTResource : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATNTResource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddToResourceQueue();
};
