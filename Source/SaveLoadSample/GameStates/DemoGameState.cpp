// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameState.h"

#include "AIController.h"
#include "../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/clsocket/src/ActiveSocket.h"
#include "Kismet/GameplayStatics.h"
#include "SaveLoadSample/DemoSaveGame/DemoSaveGame.h"
#include "SaveLoadSample/Interfaces/ISavableObject.h"
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
		auto RestoredActor = World->SpawnActor<AActor>(DataRecords[i].ActorClass,
			DataRecords[i].ActorTransform.GetLocation(),
			DataRecords[i].ActorTransform.GetRotation().Rotator());
		RestoredActor->SetActorLabel(DataRecords[i].ActorName);
		if(UKismetSystemLibrary::DoesImplementInterface(RestoredActor, USavableObject::StaticClass()))
			ISavableObject::Execute_LoadFromFSaveDataRecord(RestoredActor, DataRecords[i]);
		
	}
	
	DataRecords.Empty();
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

void ADemoGameState::ClearActors() const
{
	TArray<AActor*> FindActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USavableObject::StaticClass(), FindActors);
	for(const auto Actor : FindActors)
		Actor->Destroy();

}

