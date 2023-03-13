// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveLoadSample/Structs/FSaveDataRecord.h"
#include "UObject/Object.h"
#include "SaveLoadObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SAVELOADSAMPLE_API USaveLoadObject : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category=SaveLoad)
	FSaveDataRecord GetSaveDataForObject(UObject* SavableObject) const;

	UFUNCTION(BlueprintCallable, Category=SaveLoad)
	void LoadObjectFormSaveData(UObject* SavableObject, FSaveDataRecord Record);
};
