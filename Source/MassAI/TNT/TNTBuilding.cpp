// Fill out your copyright notice in the Description page of Project Settings.


#include "TNTBuilding.h"

#include "TNTBuildingSubsystem.h"

// Sets default values
ATNTBuilding::ATNTBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SmartObjectComponent = CreateDefaultSubobject<USmartObjectComponent>(TEXT("SmartObjectComponent"));
	SetRootComponent(SmartObjectComponent);
}

// Called when the game starts or when spawned
void ATNTBuilding::BeginPlay()
{
	Super::BeginPlay();

	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;
	TimerDelegate.BindLambda([this]()
	{
		GetWorld()->GetSubsystem<UTNTBuildingSubsystem>()->AddBuilding(SmartObjectComponent->GetRegisteredHandle(),
		                                                               Floors);
	});
	GetWorldTimerManager().SetTimer(TimerHandle,TimerDelegate, 0.5f, false);
}

// Called every frame
void ATNTBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
