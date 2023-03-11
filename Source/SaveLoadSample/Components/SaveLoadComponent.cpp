// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadComponent.h"

#include "Serialization/ObjectAndNameAsStringProxyArchive.h"


USaveLoadComponent::USaveLoadComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USaveLoadComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void USaveLoadComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FSaveDataRecord USaveLoadComponent::GetFSaveDataRecord() const
{
	FSaveDataRecord Record = FSaveDataRecord();

	auto OwnerActor = GetOwner();
	if(!OwnerActor)
		return Record;

	Record.ActorClass = OwnerActor->GetClass();
	Record.ActorName = OwnerActor->GetName();
	Record.ActorTransform = OwnerActor->GetTransform();

	FMemoryWriter Writer = FMemoryWriter(Record.BinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Writer, false);
	Ar.ArIsSaveGame = true;

	OwnerActor->Serialize(Ar);
	
	return Record;
	
}

void USaveLoadComponent::LoadFromFSaveDataRecord(FSaveDataRecord Record) const
{
	auto OwnerActor = GetOwner();
	if(!OwnerActor)
		return;

	FMemoryReader Reader = FMemoryReader(Record.BinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Reader, false);
	Ar.ArIsSaveGame = true;
	
	OwnerActor->Serialize(Ar);
}

