#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OnlineSessionSettings.h"
#include "MPT_SessionInfos.generated.h"

USTRUCT(BlueprintType)
struct MULTIPLAYERTEMPLATE_API FMPT_SessionInfos
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionInfos")
	FName SessionName;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SessionInfos")
	FOnlineSessionSearchResult* SessionSearchResult;

};