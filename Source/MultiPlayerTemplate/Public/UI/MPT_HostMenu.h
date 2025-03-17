// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/MPT_LevelInfos.h"
#include "MPT_HostMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API UMPT_HostMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	/*Name of Session*/
	UPROPERTY(BlueprintReadWrite, Category = HostMenu)
	FString SessionName;
	/* Name of the map used for the Game session */
	UPROPERTY(BlueprintReadOnly, Category = HostMenu)
	FString MapName;
	/* Disable or Enable the presence property*/
	UPROPERTY(BlueprintReadWrite, Category = HostMenu)
	bool IsPresence;
	/* Disable or Enable the LAN property*/
	UPROPERTY(BlueprintReadWrite, Category = HostMenu)
	bool IsLAN;
	/* Player max in the Game Session */
	UPROPERTY(BlueprintReadOnly, Category = HostMenu)
	int PlayersMax = 32;

	/* Index of Map */
	UPROPERTY()
	int MapIndex = 0;

	/* Map List selectable for Game Session */
	TArray<FMPT_LevelInfos*> MapList;
	/* Map info selected */
	FMPT_LevelInfos* MapInfosSelected;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	/** 
	* Increase Player max value 
	*/
	UFUNCTION(BlueprintCallable, Category = HostMenu)
	void MorePlayer();
	/* Decrease Player max value */
	UFUNCTION(BlueprintCallable, Category = HostMenu)
	void LessPlayer();
	
	/** 
	* Select next map in the map list
	*/
	UFUNCTION(BlueprintCallable, Category = HostMenu)
	void NextMap();
	/**
	* Select Previous map in the map list
	*/
	UFUNCTION(BlueprintCallable, Category = HostMenu)
	void PreviousMap();

	/**
	* Return at the Main menu
	*/
	UFUNCTION(BlueprintCallable, Category = HostMenu)
	void Return();

	/**
	* Create the Game Session
	*/
	UFUNCTION(BlueprintCallable, Category = HostMenu)
	void CreateHost();

	
};
