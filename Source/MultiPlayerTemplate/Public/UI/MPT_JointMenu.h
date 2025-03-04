// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/MPT_SessionInfos.h"
#include "MPT_JointMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API UMPT_JointMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* 
	*/
	void SetSessionSelected(UWidget* LineSelected, FMPT_SessionInfos* NewSessionSelected);

protected:

	/* Panel to attached the the result lines */
	UPROPERTY(BlueprintReadWrite, Category = JointMenu)
	class UPanelWidget* RootListPanel;
	/* référence to the button for joint the game session selected */
	UPROPERTY(BlueprintReadWrite, Category = JointMenu)
	class UButton* JointSessionBtn;
	/* Loading Widget Popup */
	UPROPERTY(BlueprintReadWrite, Category = JointMenu)
	class UMPT_LoadingPopup* LoadingWidget;

	/*Name of Session seached*/
	UPROPERTY(BlueprintReadWrite, Category = JointMenu)
	FText SessionName;
	/* Filter for Seached all session in Lan */
	UPROPERTY(BlueprintReadWrite, Category = JointMenu)
	bool bIsLAN;
	/*  */
	UPROPERTY(BlueprintReadWrite, Category = JointMenu)
	bool bIsPresent;

	/** Event handlers */
	FDelegateHandle SearchSessionEvent;

	/* Widget tamplate for result line */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = JointMenu)
	TSubclassOf<class UMPT_SearchResultLine> ResultLine;

	/* Widget tamplate for loading pupope */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = JointMenu)
	TSubclassOf<class UMPT_LoadingPopup> LoadingPopup;

	/* Indicate if the loading screen is visible or not */
	UPROPERTY(BlueprintReadOnly, Category = JointMenu)
		bool LoadingVisible;

	/* list of all resulte line */
	TArray<class USearchResultLine*> SearchResultLineList;

	/* Game Session selected */
	FMPT_SessionInfos* SessionSelected;


	//virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	/**
	* Joint the Game session selected
	*/
	UFUNCTION(BlueprintCallable, Category = JointMenu)
	void Joint();

	/**
	* Search all the Game session
	*/
	UFUNCTION(BlueprintCallable, Category = JointMenu)
	void Search();

	/**
	* Return to the main menu
	*/
	UFUNCTION(BlueprintCallable, Category = JointMenu)
	void Return();

	/**
	* Actions to do When the search function is end
	* @param SessionResult - Results of the search 
	* @param bWasSuccessful - Say if the search was successful
	*/
	void ResultActions(const TSharedPtr<class FOnlineSessionSearch>& SessionResult, bool bWasSuccessful);
	
	/**
	* Instentiates the Result line widget based on results infos
	* @param SessionSearchResultInfos - Results Infos of search
	*/
	void InstentiateResultLine(FOnlineSessionSearchResult* SessionSearchResultInfos);
};
