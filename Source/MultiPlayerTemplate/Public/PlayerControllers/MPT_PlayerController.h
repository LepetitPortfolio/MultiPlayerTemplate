// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MPT_PlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API AMPT_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
	virtual void BeginPlay() override;

	
};
