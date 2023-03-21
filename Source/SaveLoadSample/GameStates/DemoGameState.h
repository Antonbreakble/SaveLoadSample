// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SaveLoadSample/Structs/FActorDataRecord.h"
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
	void SaveGameToSlot(FString SlotName);

	UFUNCTION(BlueprintCallable, Category=SaveLoad)
	void LoadFromSlot(FString SlotName);
private:
	UPROPERTY(SaveGame)
	TArray<FActorDataRecord> DataRecords;
private:
	void SaveActors();
	static void SaveComponentFromActors(const AActor* Actor, FActorDataRecord& ActorDataRecord);
	static void LoadComponentToActor(const AActor* Actor, TArray<FSaveDataRecord> ComponentData);
	void ClearActors() const;
};
