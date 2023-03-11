// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SaveLoadSample/Structs/FSaveDataRecord.h"
#include "SaveLoadComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SAVELOADSAMPLE_API USaveLoadComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USaveLoadComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
public:
	UFUNCTION(BlueprintCallable, Category=SaveLoad)
	FSaveDataRecord GetFSaveDataRecord() const;
	UFUNCTION(BlueprintCallable, Category=SaveLoad)
	void LoadFromFSaveDataRecord(FSaveDataRecord Record) const;
};
