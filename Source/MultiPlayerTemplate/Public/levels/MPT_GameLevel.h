// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MPT_GameLevel.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API AMPT_GameLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
