// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RoomExitComponent.generated.h"


class UBoxComponent;
class UArrowComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONGENERATION_API URoomExitComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	URoomExitComponent();


protected:
	virtual void BeginPlay() override;
	
	
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> ExitBoxOverlap;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UArrowComponent> ArrowExitDirection;

public:	

	bool IsExitOverlapAnotherRoom();
		
};

