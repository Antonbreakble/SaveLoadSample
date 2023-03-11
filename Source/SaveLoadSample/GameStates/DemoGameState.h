// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SaveLoadSample/Structs/FSaveDataRecord.h"
#include "UObject/Object.h"
#include "DemoGameState.generated.h"

/**
 * 
 */
UCLASS()
class SAVELOADSAMPLE_API ADemoGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ADemoGameState();
	UFUNCTION(BlueprintCallable, Category=SaveLoad)
	void SaveGameToSlot();
private:
	UPROPERTY(SaveGame)
	TArray<FSaveDataRecord> DataRecords;
private:
	void SaveActors();
};
