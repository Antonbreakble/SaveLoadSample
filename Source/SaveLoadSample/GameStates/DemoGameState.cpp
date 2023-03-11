// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameState.h"

#include "Kismet/GameplayStatics.h"
#include "SaveLoadSample/Interfaces/ISavableObject.h"

ADemoGameState::ADemoGameState()
{
}

void ADemoGameState::SaveGameToSlot()
{
	SaveActors();
}

void ADemoGameState::SaveActors()
{
	TArray<AActor*> FindActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USavableObject::StaticClass(), FindActors);
	for(const auto Actor : FindActors)
	{
		DataRecords.Add(ISavableObject::Execute_GetFSaveDataRecord(Actor));
	}
}
