// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonMaster.generated.h"

class ADungeonRoom;
class URoomExitComponent;

UCLASS()
class DUNGEONGENERATION_API ADungeonMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	ADungeonMaster();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults|GeneratorSettings")
	TArray<TSubclassOf<ADungeonRoom>> StartRoomsPresets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults|GeneratorSettings")
	TArray<TSubclassOf<ADungeonRoom>> RoomsPresets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults|GeneratorSettings")
	int32 RoomNums = 10;
	
protected:
	virtual void BeginPlay() override;


public:
	void GenerateLevel();

	
private:
	
	void SpawnStartRoom();
	void SpawnRooms();
	void SpawnDoors();

	
	UPROPERTY()
	TArray<URoomExitComponent*> RoomsExits;
	
	UPROPERTY()
	TArray<ADungeonRoom*> Rooms;
};
