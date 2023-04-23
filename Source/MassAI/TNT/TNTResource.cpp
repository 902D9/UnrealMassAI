// Fill out your copyright notice in the Description page of Project Settings.


#include "TNTResource.h"

#include "SmartObjectComponent.h"
#include "TNTBuildingSubsystem.h"

// Sets default values
ATNTResource::ATNTResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ATNTResource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATNTResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATNTResource::AddToResourceQueue()
{
	if(const USmartObjectComponent* SOComponent = FindComponentByClass<USmartObjectComponent>())
	{
		FSmartObjectHandle SmartObjectHandle =  SOComponent->GetRegisteredHandle();
		GetWorld()->GetSubsystem<UTNTBuildingSubsystem>()->AddResourceQueue(SmartObjectHandle);
	}
}

