#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FSaveDataRecord.generated.h"

USTRUCT(BlueprintType)
struct FSaveDataRecord
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UClass* ActorClass;

	UPROPERTY()
	FString ActorName;

	UPROPERTY()
	FTransform ActorTransform;

	UPROPERTY()
	TArray<uint8> BinaryData;
};

