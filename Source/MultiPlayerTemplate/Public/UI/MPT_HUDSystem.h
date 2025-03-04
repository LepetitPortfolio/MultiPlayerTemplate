// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Enums/MPT_GameStateType.h"

#include "MPT_HUDSystem.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API AMPT_HUDSystem : public AHUD
{
	GENERATED_BODY()
	
public:
	/**
	* Change the Widget based on Game state
	* @param NewState - New Game state
	*/
	void OnGameStateChange(EGameStateType NewState);

protected:

	virtual void BeginPlay() override;

	/* Map of Widget template by Game State */
	UPROPERTY(EditDefaultsOnly, Category = HUDSystem)
	TMap<EGameStateType, TSubclassOf<UUserWidget>> UIByGameStep;

private:
	/* Reference to Widget active */
	UPROPERTY()
	UUserWidget* ActiveUI;

	/**
	* Instanciate the Widget based on Game State
	* @param NewState - New Game Satet
	* @return the new Widget
	*/
	UUserWidget* InstatiateUserWidget(EGameStateType NewState);

	/**
	* Display the widget
	* @param NewWidget - Widget to displayed
	*/
	void DisplayWidget(UUserWidget* NewWidget);

};
