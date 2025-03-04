#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"


/**
* 
*/
UENUM(BlueprintType)
enum class EGameStateType : uint8
{
	None,
	MainMenu,
	HostMenu,
	JointMenu,
	Loading,
	InGame,
	Max			UMETA(Hidden)
};