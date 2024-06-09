// Fill out your copyright notice in the Description page of Project Settings.


#include "DMG/Rooms/RoomExitComponent.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

URoomExitComponent::URoomExitComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	ExitBoxOverlap = CreateDefaultSubobject<UBoxComponent>("ExitBoxOverlap");
	ExitBoxOverlap->SetupAttachment(this);
	ExitBoxOverlap->SetCollisionObjectType(ECC_WorldStatic);
	ExitBoxOverlap->SetCollisionResponseToAllChannels(ECR_Ignore);
	ExitBoxOverlap->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	
	ArrowExitDirection = CreateDefaultSubobject<UArrowComponent>("ArrowExitDirection");
	ArrowExitDirection->SetupAttachment(this);
	ArrowExitDirection->SetArrowSize(5.f);
	ArrowExitDirection->SetArrowColor(FColor::Emerald);

}

void URoomExitComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

bool URoomExitComponent::IsExitOverlapAnotherRoom()
{
	TArray<AActor*> Actors;
	ExitBoxOverlap->GetOverlappingActors(Actors);
	return Actors.Num() != 0;;
}



