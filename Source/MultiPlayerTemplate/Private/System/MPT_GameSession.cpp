#include "System/MPT_GameSession.h"
#include "Online/OnlineSessionNames.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "UI/MPT_HUDSystem.h"
#include "OnlineSessionSettings.h"



AMPT_GameSession::AMPT_GameSession(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &AMPT_GameSession::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &AMPT_GameSession::OnStartOnlineGameComplete);

	/* Bind function for FINDING a Session */
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &AMPT_GameSession::OnFindSessionsComplete);

	/* Bind function for JOINING a Session */
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &AMPT_GameSession::OnJoinSessionComplete);

	/* Bind function dor DESTROYING a Session */
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &AMPT_GameSession::OnDestroySessionComplete);
}

void AMPT_GameSession::SetGameInstance(UGameInstance* NewGameInstance)
{
	if (NewGameInstance)
	{
		GameInstance = NewGameInstance;
	}
}

bool AMPT_GameSession::HostSession(UWorld* World, FUniqueNetIdPtr UserId, FString SessionN, FString MapName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
	CurrentWorld = World;
	return HostSession(UserId, SessionN, MapName, bIsLAN, bIsPresence, MaxNumPlayers);
}

bool AMPT_GameSession::HostSession(FUniqueNetIdPtr UserId, FString SessionN, FString MapName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
	//RegisterServer();

	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if ((Sessions.IsValid()) && (UserId.IsValid()))
		{
			SessionSettings = MakeShareable(new FOnlineSessionSettings());
			//SessionSettings = new FOnlineSessionSettings();

			SessionSettings->bIsLANMatch = bIsLAN;
			SessionSettings->bUsesPresence = bIsPresence;
			SessionSettings->NumPublicConnections = MaxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;


			/*//SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;*/

			SessionSettings->Set(SETTING_MAPNAME, MapName, EOnlineDataAdvertisementType::ViaOnlineService);

			if (!SessionN.IsEmpty())
			{
				FOnlineSessionSetting CustomSetting;
				CustomSetting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
				CustomSetting.Data = SessionN;
				SessionSettings->Settings.Add(FName("SESSION_NAME"), CustomSetting);
			}

			OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

			return Sessions->CreateSession(*UserId, FName(SessionN), *SessionSettings);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("No OnlineSubsystem found !"));
	}
	return false;
}

void AMPT_GameSession::OnCreateSessionComplete(FName SessionN, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("OnCreateSession Complete %s, %d"), *SessionN.ToString(), bWasSuccessful));

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{

			Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);

			if (bWasSuccessful)
			{
				OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);

				Sessions->StartSession(SessionN);
			}
		}
	}
}

void AMPT_GameSession::OnStartOnlineGameComplete(FName SessionN, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("OnStartSession Complete %s, ùd"), *SessionN.ToString(), bWasSuccessful));

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		}
	}

	if (bWasSuccessful)
	{
		FString MapName;
		SessionSettings.Get()->Get(SETTING_MAPNAME, MapName);
		UGameplayStatics::OpenLevel(CurrentWorld, FName(MapName), true, "Listen");
	}
}

void AMPT_GameSession::FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if ((Sessions.IsValid()) && (UserId.IsValid()))
		{
			SessionSearch = MakeShareable(new FOnlineSessionSearch());

			SessionSearch->bIsLanQuery = bIsLAN;
			SessionSearch->MaxSearchResults = 20;
			SessionSearch->PingBucketSize = 50;

			if (bIsPresence)
			{
				SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
			}

			TSharedRef<FOnlineSessionSearch> SearchSettingRef = SessionSearch.ToSharedRef();

			OnFindSessionsCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);

			Sessions->FindSessions(*UserId, SearchSettingRef);
		}
	}
	else
	{
		OnFindSessionsComplete(false);
	}
}

void AMPT_GameSession::OnFindSessionsComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("OnFindSessionsComplete : %d"), bWasSuccessful));

	const IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			Sessions->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Num Search Results : %d"), SessionSearch->SearchResults.Num()));

			if (SessionSearch->SearchResults.Num() > 0)
			{
				for (int32 SearchIndex = 0; SearchIndex < SessionSearch->SearchResults.Num(); SearchIndex++)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Session Number : %d | SessionN : %s"), SearchIndex + 1, *(SessionSearch->SearchResults[SearchIndex].Session.OwningUserName)));
				}
			}
		}
	}

	EventAfterFindigSession.Broadcast(SessionSearch, bWasSuccessful);
}

bool AMPT_GameSession::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionN, const FOnlineSessionSearchResult& SearchResult)
{
	bool bSuccessful = false;

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if ((Sessions.IsValid()) && (UserId.IsValid()))
		{
			UWorld* World = GameInstance->GetWorld();
			PlayerController = UGameplayStatics::GetPlayerController(World, 0);
			OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);

			bSuccessful = Sessions->JoinSession(*UserId, SessionN, SearchResult);
		}
	}
	return bSuccessful;
}

void AMPT_GameSession::OnJoinSessionComplete(FName SessionN, EOnJoinSessionCompleteResult::Type Result)
{
	GEngine->AddOnScreenDebugMessage(-1, -10.0f, FColor::Red, FString::Printf(TEXT("OnJoinSessionComplete %s, %d"), *SessionN.ToString(), static_cast<int32>(Result)));

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);			

			FString TravelURL;

			if ((PlayerController) && (Sessions->GetResolvedConnectString(SessionN, TravelURL)))
			{
				PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);	
			}
		}
	}

}

void AMPT_GameSession::OnDestroySessionComplete(FName SessionN, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("OnDestroySessionComplete %s, %d"), *SessionN.ToString(), bWasSuccessful));

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			Sessions->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);

			if (bWasSuccessful)
			{
				UGameplayStatics::OpenLevel(GetWorld(), "ThirdPersonExampleMap", true);
			}
		}
	}
}


