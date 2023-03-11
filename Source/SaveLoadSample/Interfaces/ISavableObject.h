// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveLoadSample/Structs/FSaveDataRecord.h"
#include "UObject/Interface.h"
#include "ISavableObject.generated.h"

UINTERFACE()
class USavableObject : public UInterface
{
	GENERATED_BODY()
};

class SAVELOADSAMPLE_API ISavableObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=SaveLoad)
	FSaveDataRecord GetFSaveDataRecord();
	virtual FSaveDataRecord GetFSaveDataRecord_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=SaveLoad)
	void LoadFromFSaveDataRecord(FSaveDataRecord Record);
	virtual void LoadFromFSaveDataRecord_Implementation(FSaveDataRecord Record);
};
