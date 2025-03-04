// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MPT_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API UMPT_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	/**
	* Open the Host menu
	*/
	UFUNCTION(BlueprintCallable, Category = MainMenu)
	void OpenHostMenu();

	/**
	* Open the Join menu
	*/
	UFUNCTION(BlueprintCallable, Category = MainMenu)
	void OpenJoinMenu();

	/**
	* Quit the game
	*/
	UFUNCTION(BlueprintCallable, Category = MainMenu)
	void Quit();

};
