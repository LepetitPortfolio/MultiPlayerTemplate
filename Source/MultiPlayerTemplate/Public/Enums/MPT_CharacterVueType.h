#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"


/**
* 
*/
UENUM(BlueprintType)
enum class ECharacterVueType : uint8
{
	FPS,
	TPS,
	FTPS,
	Max			UMETA(Hidden)
};