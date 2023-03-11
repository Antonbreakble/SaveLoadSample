
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UObject/Object.h"
#include "DemoSaveGame.generated.h"

UCLASS()
class SAVELOADSAMPLE_API UDemoSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<uint8> ByteData;
};
