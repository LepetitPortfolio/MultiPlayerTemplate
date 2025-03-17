// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/MPT_SessionInfos.h"
#include "MPT_SearchResultLine.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API UMPT_SearchResultLine : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* Initialise all values of the result line
	* @param NewJointMenu - reference to the joint menu
	* @param SessionSearchResultInfos - Result Infos
	*/
	void InitValues(class UMPT_JointMenu* NewJointMenu, FOnlineSessionSearchResult* SessionSearchResultInfos);

	/**
	* Getter of Game Session info
	* @return reference to the Game Session info
	*/
	FMPT_SessionInfos GetSessionInfos() { return SessionInfos; }

protected:

	UPROPERTY()
	class UMPT_JointMenu* JointMenu;

	/* Name of Game session */
	UPROPERTY(BlueprintReadWrite, Category = SearchResultLine)
	FString SessionName = "Test";

	/* Number of player connected */
	UPROPERTY(BlueprintReadWrite, Category = SearchResultLine)
	int32 PlayerConnected = 0;
	/* Number of player max connected */
	UPROPERTY(BlueprintReadWrite, Category = SearchResultLine)
	int32 MaxPlayer = 32;
	
	/* Infos of game session */
	FMPT_SessionInfos SessionInfos;

	/**
	* Action on click
	*/
	UFUNCTION(BlueprintCallable, Category = SearchResultLine)
	void OnClickAction();


};
