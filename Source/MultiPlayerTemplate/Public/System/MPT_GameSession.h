// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
//#include "Online/OnlineSessionNames.h"
#include "GameFramework/GameSession.h"
#include "MPT_GameSession.generated.h"

DECLARE_EVENT_TwoParams(UNetworkSystem, FFindSessionEvent, const TSharedPtr<class FOnlineSessionSearch>&, bool)

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API AMPT_GameSession : public AGameSession
{
	GENERATED_BODY()

public:

	AMPT_GameSession(const FObjectInitializer& ObjectInitializer);


	void SetGameInstance(UGameInstance* NewGameInstance);

	/* Create Session */

	bool HostSession(UWorld* World, TSharedPtr<const FUniqueNetId> UserId, FString SessionN, FString MapName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	/**
	*	Function to host a game!
	*	@Param		UserID			User that started the request
	*	@Param		SessionN		Name of the Session
	*	@Param		MapName			Name of the Map
	*	@Param		bIsLAN			Is this is LAN Game?
	*	@Param		bIsPresence		"Is the Session to create a presence Session"
	*	@Param		MaxNumPlayers	        Number of Maximum allowed players on this "Session" (Server)
	*/
	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FString SessionN, FString MapName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);


	/* Find Session */

	/**
	*	Find an online session
	*	@param UserId user that initiated the request
	*	@param bIsLAN are we searching LAN matches
	*	@param bIsPresence are we searching presence sessions
	*/
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);


	/* Join Session */

	/**
	*	Joins a session via a search result
	*	@param SessionN name of session
	*	@param SearchResult Session to join
	*
	*	@return bool true if successful, false otherwise
	*/
	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionN, const FOnlineSessionSearchResult& SearchResult);


	/* Destroy Session */

	/**
	*	Delegate fired when a destroying an online session has completed
	*	@param SessionN the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnDestroySessionComplete(FName SessionN, bool bWasSuccessful);

	inline TSharedPtr<class FOnlineSessionSearch>* GetSessionSearch() { return &SessionSearch; }

	inline FFindSessionEvent* GetEventAfterFindigSession() { return &EventAfterFindigSession; }


protected:

	UPROPERTY()
	UWorld* CurrentWorld = nullptr;

	UPROPERTY()
	UGameInstance* GameInstance;

	/* Create Session */

	/* Delegate called when session created */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	/* Delegate called when session started */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	/* Handles to registered delegate for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	/**
	*	Function fired when a session create request has completed
	*	@param SessionN the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	UFUNCTION()
	virtual void OnCreateSessionComplete(FName SessionN, bool bWasSuccessful);

	/**
	*	Function fired when a session start request has completed
	*	@param SessionN the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	UFUNCTION()
	void OnStartOnlineGameComplete(FName SessionN, bool bWasSuccessful);


	/* Find Session */

	/* Delegate for searching for session */
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	/* Handle to registered deleguate for searching a session */
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	FFindSessionEvent EventAfterFindigSession;

	/**
	*	Delegate fired when a session search query has completed
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnFindSessionsComplete(bool bWasSuccessful);


	/* Join Session */

	/* Delegate for joining a session */
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	/* Handle to registered delegate for joining a session */
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	UPROPERTY()
	APlayerController* PlayerController;

	/**
	*	Delegate fired when a session join request has complete
	*	@param SessionN the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnJoinSessionComplete(FName SessionN, EOnJoinSessionCompleteResult::Type Result);


	/* Destroy Session */

	/* Delegate for destroying a session */
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	/* Handle to registered delegate for destroying a session */
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
	
};
