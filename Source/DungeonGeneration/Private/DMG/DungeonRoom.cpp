// Fill out your copyright notice in the Description page of Project Settings.


#include "DMG/DungeonRoom.h"

#include "Components/BoxComponent.h"

ADungeonRoom::ADungeonRoom()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;


	RoomOverlapBox = CreateDefaultSubobject<UBoxComponent>("RoomOverlapBox");
	RoomOverlapBox->SetupAttachment(RootComponent);
}

void ADungeonRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ADungeonRoom::IsOverlappedOtherRooms() 
{
	TArray<AActor*> Actors;
	RoomOverlapBox->GetOverlappingActors(Actors, ADungeonRoom::StaticClass());
	return Actors.Num() != 0;
}



