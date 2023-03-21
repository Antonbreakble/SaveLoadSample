// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadObject.h"

#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

FSaveDataRecord USaveLoadObject::GetSaveDataForObject(UObject* SavableObject) const
{
	FSaveDataRecord Record = FSaveDataRecord();
	Record.ActorClass =  SavableObject->GetClass();
	Record.ActorName = SavableObject->GetName();
	if(const auto Actor = Cast<AActor>(SavableObject))
	{
		Record.ActorTransform = Actor->GetTransform();
	}
	
	FMemoryWriter Writer = FMemoryWriter(Record.BinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Writer, false);
	Ar.ArIsSaveGame = true;

	SavableObject->Serialize(Ar);
	
	return Record;
	
}

void USaveLoadObject::LoadObjectFormSaveData(UObject* SavableObject, FSaveDataRecord Record)
{
	FMemoryReader Reader = FMemoryReader(Record.BinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Reader, false);
	Ar.ArIsSaveGame = true;

	SavableObject->Serialize(Ar);

	return;
}
