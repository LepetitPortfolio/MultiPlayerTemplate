#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MPT_Interactable.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UMPT_Interactable : public UInterface
{
	GENERATED_BODY()
	
};

class MULTIPLAYERTEMPLATE_API IMPT_Interactable
{
	GENERATED_BODY()

public:
	virtual void Interact(AActor* _InteractingActor) = 0;
};
