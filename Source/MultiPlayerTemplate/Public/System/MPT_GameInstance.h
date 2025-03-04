// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MPT_GameSession.h"

#include "Structs/MPT_LevelInfos.h"

#include "MPT_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API UMPT_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMPT_GameInstance(const FObjectInitializer& ObjectInitializer);

	AMPT_GameSession* GetNetworkSystem() { return NetworkSystem; }

	UDataTable* GetLevelInfos() { return LevelInfos; }

	virtual void Init() override; 

protected :

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MPT_GameInstance")
	UDataTable* LevelInfos;

private:
	UPROPERTY()
	AMPT_GameSession* NetworkSystem = nullptr;
	
};
