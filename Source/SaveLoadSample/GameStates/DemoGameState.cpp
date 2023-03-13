// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameState.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "SaveLoadSample/DemoSaveGame/DemoSaveGame.h"
#include "SaveLoadSample/Interfaces/ISavableObject.h"
#include "SaveLoadSample/Structs/FActorDataRecord.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

ADemoGameState::ADemoGameState()
{
}

void ADemoGameState::SaveGameToSlot(FString SlotName)
{
	DataRecords.Empty();
	SaveActors();

	TArray<uint8> BinaryData;
	FMemoryWriter Writer = FMemoryWriter(BinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Writer, false);
	Ar.ArIsSaveGame = true;

	Serialize(Ar);

	auto SaveInstance = Cast<UDemoSaveGame>(UGameplayStatics::CreateSaveGameObject(UDemoSaveGame::StaticClass()));
	SaveInstance->ByteData = BinaryData;
	UGameplayStatics::SaveGameToSlot(SaveInstance, SlotName, 0);
	
}

void ADemoGameState::LoadFromSlot(FString SlotName)
{
	DataRecords.Empty();
	ClearActors();

	auto LoadGameInstance = Cast<UDemoSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if(!LoadGameInstance)
		return;
	TArray<uint8> BinaryData = LoadGameInstance->ByteData;
	FMemoryReader Reader = FMemoryReader(BinaryData);
	FObjectAndNameAsStringProxyArchive Ar(Reader, false);
	Ar.ArIsSaveGame = true;

	Serialize(Ar);

	auto World = GetWorld();
	for (auto i = 0; i < DataRecords.Num(); ++i)
	{
		auto RestoredActor = World->SpawnActor<AActor>(DataRecords[i].ActorData.ActorClass,
			DataRecords[i].ActorData.ActorTransform.GetLocation(),
			DataRecords[i].ActorData.ActorTransform.GetRotation().Rotator());
		
		RestoredActor->SetActorLabel(DataRecords[i].ActorData.ActorName);
		
		if(UKismetSystemLibrary::DoesImplementInterface(RestoredActor, USavableObject::StaticClass()))
		{
			LoadComponentToActor(RestoredActor, DataRecords[i].ComponentData);
			ISavableObject::Execute_LoadFromFSaveDataRecord(RestoredActor, DataRecords[i].ActorData);
		}
		
	}
	
	DataRecords.Empty();
}

void ADemoGameState::SaveActors()
{
	TArray<AActor*> FindActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USavableObject::StaticClass(), FindActors);
	for(const auto Actor : FindActors)
	{
		FActorDataRecord ActorDataRecord = FActorDataRecord();
		ActorDataRecord.ActorData = ISavableObject::Execute_GetFSaveDataRecord(Actor);
		SaveComponentFromActors(Actor, ActorDataRecord);
		DataRecords.Add(ActorDataRecord);
	}
}

void ADemoGameState::SaveComponentFromActors(const AActor* Actor, FActorDataRecord& ActorDataRecord)
{
	auto SavableComponents = Actor->GetComponentsByInterface(USavableObject::StaticClass());
	for(UActorComponent* SavableComponent : SavableComponents)
	{
		ActorDataRecord.ComponentData.Add(ISavableObject::Execute_GetFSaveDataRecord(SavableComponent));
	}
}

void ADemoGameState::LoadComponentToActor(const AActor* Actor, TArray<FSaveDataRecord> ComponentData)
{
	auto SavableComponent = Actor->GetComponentsByInterface(USavableObject::StaticClass());
	for(auto i = 0; i < ComponentData.Num(); i++)
	{
		auto ComponentName = ComponentData[i].ActorName;

		auto AvailableComponent = SavableComponent.FindByPredicate([ComponentName](const UActorComponent* Component)
		{
			return ComponentName == Component->GetName();
		});
		
		if(!AvailableComponent)
			continue;
		
		FMemoryReader Reader = FMemoryReader(ComponentData[i].BinaryData);
		FObjectAndNameAsStringProxyArchive Ar(Reader, false);
		Ar.ArIsSaveGame = true;
		
		(*AvailableComponent)->Serialize(Ar);
	}
}

void ADemoGameState::ClearActors() const
{
	TArray<AActor*> FindActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USavableObject::StaticClass(), FindActors);
	for(const auto Actor : FindActors)
		Actor->Destroy();

}

