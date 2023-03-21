
#pragma once

#include "CoreMinimal.h"
#include "FSaveDataRecord.h"
#include "UObject/Object.h"
#include "FActorDataRecord.generated.h"

USTRUCT(BlueprintType)
struct FActorDataRecord
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame)
	FSaveDataRecord ActorData;
	UPROPERTY(SaveGame)
	TArray<FSaveDataRecord> ComponentData;
};