// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonRoom.generated.h"

class URoomExitComponent;
class UBoxComponent;

UCLASS()
class DUNGEONGENERATION_API ADungeonRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	ADungeonRoom();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> RoomOverlapBox;

public:	

	bool IsOverlappedOtherRooms();

};
