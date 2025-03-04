// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MPT_InGameScreen.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API UMPT_InGameScreen : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite, Category = InGameScreen)
	class UScaleBox* InGameMenu;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;


};
