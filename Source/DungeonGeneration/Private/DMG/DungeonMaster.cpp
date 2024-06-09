// Fill out your copyright notice in the Description page of Project Settings.


#include "DMG/DungeonMaster.h"

#include "DMG/DungeonRoom.h"
#include "DMG/Rooms/RoomExitComponent.h"

ADungeonMaster::ADungeonMaster()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADungeonMaster::BeginPlay()
{
	Super::BeginPlay();
	GenerateLevel();
}

void ADungeonMaster::GenerateLevel()
{
	SpawnStartRoom();
	SpawnRooms();
	SpawnDoors();
	// GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([this]()
	// {
	// 	
	// }));
	
}

void ADungeonMaster::SpawnStartRoom()
{
	if (const TSubclassOf<ADungeonRoom> StartRoomClass = StartRoomsPresets[FMath::RandRange(
		0, StartRoomsPresets.Num() - 1)])
	{
		// Spawn Start Room
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ADungeonRoom* StartRoom = GetWorld()->SpawnActor<ADungeonRoom>(
			StartRoomClass, FTransform(), SpawnParameters);

		// Get All Exits/Connections to room;
		TArray<URoomExitComponent*> Exits;
		StartRoom->GetComponents(URoomExitComponent::StaticClass(), Exits);
		RoomsExits.Append(Exits);
		Rooms.Add(StartRoom);
	}
}

void ADungeonMaster::SpawnRooms()
{
	if (RoomsExits.IsEmpty()) return;
	int32 i = RoomNums - 1;
	while (i > 0)
	{
		URoomExitComponent* RoomConnection = RoomsExits[FMath::RandRange(0, RoomsExits.Num() - 1)];
		TSubclassOf<ADungeonRoom> RoomClass = RoomsPresets[FMath::RandRange(0, RoomsPresets.Num() - 1)];

		// Check space is free 1:Phase
		// FHitResult HitResult;
		// FVector StartLocation = RoomConnection->GetComponentLocation();
		// FVector EndLocation = StartLocation + RoomConnection->GetForwardVector() * 1000.f;
		// GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_WorldStatic);
		// DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 30.f);
		// if(HitResult.bBlockingHit)
		// {
		//
		// 	DrawDebugSphere(GetWorld(), StartLocation, 100.f, 16,  FColor::Red, false, 30.f);
		// 	RoomsConnections.Remove(RoomConnection);
		// 	continue;
		// }
		if(RoomConnection->IsExitOverlapAnotherRoom())
		{
			RoomsExits.Remove(RoomConnection);
			continue;
		}
		

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ADungeonRoom* Room = GetWorld()->SpawnActor<ADungeonRoom>(
			RoomClass, RoomConnection->GetComponentTransform(), SpawnParameters);

		// Check space is free 2:Phase
		// if (Room->IsOverlappedOtherRooms())
		// {
		// 	Room->Destroy();
		// 	RoomsExits.Remove(RoomConnection);
		// 	continue;
		// }
		
		TArray<URoomExitComponent*> Exits;
		Room->GetComponents(URoomExitComponent::StaticClass(), Exits);
		
		RoomsExits.Remove(RoomConnection);
		RoomsExits.Append(Exits);
		
		Rooms.Add(Room);
		i--;
	}
}

void ADungeonMaster::SpawnDoors()
{

	for(auto Room : Rooms)
	{
		TArray<URoomExitComponent*> Exits;
		Room->GetComponents(URoomExitComponent::StaticClass(), Exits);
		
		for (auto Exit : Exits)
		{
			if(Exit->IsExitOverlapAnotherRoom())
			{
				Exit->SetVisibility(false, true);
			}
		}
	}

}
