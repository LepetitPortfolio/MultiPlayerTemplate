#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Engine/LevelScriptActor.h"

#include "MPT_LevelInfos.generated.h"

USTRUCT(BlueprintType)
struct MULTIPLAYERTEMPLATE_API FMPT_LevelInfos : public FTableRowBase
{
	GENERATED_BODY()

public:
	/* Name of level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelInfos")
	FName LevelName = "";

	/* Reference to level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelInfos")
	TSoftObjectPtr<UWorld> Level = nullptr;

	FMPT_LevelInfos() {}
};