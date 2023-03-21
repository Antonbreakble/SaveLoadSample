#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FSaveDataRecord.generated.h"

USTRUCT(BlueprintType)
struct FSaveDataRecord
{
	GENERATED_BODY()
	
public:
	UPROPERTY(SaveGame)
	UClass* ActorClass;

	UPROPERTY(SaveGame)
	FString ActorName;

	UPROPERTY(SaveGame)
	FTransform ActorTransform;

	UPROPERTY(SaveGame)
	TArray<uint8> BinaryData;
	
};

