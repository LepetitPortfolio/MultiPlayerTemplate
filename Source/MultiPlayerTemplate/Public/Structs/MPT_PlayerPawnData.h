#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MPT_PlayerPawnData.generated.h"

USTRUCT(BlueprintType)
struct MULTIPLAYERTEMPLATE_API FMPT_PlayerPawnData
{
	GENERATED_BODY()

public:
	int32 Type;

};