// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPT_JointMenu.h"
#include "UI/MPT_SearchResultLine.h"
#include "UI/MPT_LoadingPopup.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MPT_HUDSystem.h"
#include "Components/Button.h"
//#include "System/NetworkSystem.h"
#include "System/MPT_GameSession.h"
#include "System/MPT_GameInstance.h"
#include "Components/PanelWidget.h"

/*void UJointMenu::NativePreConstruct()
{
}*/

void UMPT_JointMenu::NativeConstruct()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	UMPT_GameInstance* GameInstance = Cast<UMPT_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if ((GameInstance) && (GameInstance->GetNetworkSystem()))
	{
		SearchSessionEvent = GameInstance->GetNetworkSystem()->GetEventAfterFindigSession()->AddUObject(this, &UMPT_JointMenu::ResultActions);
	}

	if (JointSessionBtn)
	{
		JointSessionBtn->SetIsEnabled(false);
	}

	LoadingWidget = CreateWidget<UMPT_LoadingPopup>(this, LoadingPopup);


	if (LoadingWidget)
	{
		LoadingWidget->AddToViewport();
		LoadingWidget->SetIsEnabled(false);
	}

}

void UMPT_JointMenu::NativeDestruct()
{

	UMPT_GameInstance* GameInstance = Cast<UMPT_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if ((GameInstance) && (GameInstance->GetNetworkSystem()))
	{
		GameInstance->GetNetworkSystem()->GetEventAfterFindigSession()->Remove(SearchSessionEvent);
	}
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if (LoadingWidget)
	{
		LoadingWidget->SetIsEnabled(false);
		LoadingWidget->RemoveFromParent();
	}
}

void UMPT_JointMenu::Joint()
{
	if (!SessionSelected)
	{
		return;
	}

	UMPT_GameInstance* GameInstance = Cast<UMPT_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		//UNetworkSystem* NetworkSystem = GameInstance->GetNetworkSystem();
		AMPT_GameSession* NetworkSystem = GameInstance->GetNetworkSystem();

		if (NetworkSystem)
		{
			const ULocalPlayer* Player = GetGameInstance<UMPT_GameInstance>()->GetFirstGamePlayer();
			NetworkSystem->JoinSession(Player->GetPreferredUniqueNetId().GetUniqueNetId(), SessionSelected->SessionName, *SessionSelected->SessionSearchResult);
		}
	}
}

void UMPT_JointMenu::Search()
{
	if (LoadingWidget)
	{
		LoadingWidget->SetIsEnabled(true);
	}

	UMPT_GameInstance* GameInstance = Cast<UMPT_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		//UNetworkSystem* NetworkSystem = GameInstance->GetNetworkSystem();
		AMPT_GameSession* NetworkSystem = GameInstance->GetNetworkSystem();
		
		if (NetworkSystem)
		{
			const ULocalPlayer* Player = GetGameInstance<UMPT_GameInstance>()->GetFirstGamePlayer();
			NetworkSystem->FindSessions(Player->GetPreferredUniqueNetId().GetUniqueNetId(), bIsLAN, bIsPresent);
		}
	}
}

void UMPT_JointMenu::Return()
{
	AMPT_HUDSystem* HUD = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD<AMPT_HUDSystem>();

	if (HUD)
	{
		HUD->OnGameStateChange(EGameStateType::MainMenu);
	}
}

void UMPT_JointMenu::ResultActions(const TSharedPtr<class FOnlineSessionSearch>& SessionResult, bool bWasSuccessful)
{
	if (LoadingWidget)
	{
		LoadingWidget->SetIsEnabled(false);
	}

	if (!bWasSuccessful)
	{
		return;
	}

	for (int numSesssion = 0; numSesssion < SessionResult->SearchResults.Num(); numSesssion++)
	{
		InstentiateResultLine(&SessionResult->SearchResults[numSesssion]);
	}
}

void UMPT_JointMenu::InstentiateResultLine(FOnlineSessionSearchResult* SessionSearchResultInfos)
{
	UMPT_SearchResultLine* SearchResultLine =  CreateWidget<UMPT_SearchResultLine>(this, ResultLine);

	SearchResultLine->InitValues(this, SessionSearchResultInfos);

	if (RootListPanel)
	{
		RootListPanel->AddChild(SearchResultLine);
	}
}


void UMPT_JointMenu::SetSessionSelected(UWidget* LineSelected, FMPT_SessionInfos* NewSessionSelected)
{
	SessionSelected = NewSessionSelected;
	if ((SessionSelected) && (JointSessionBtn))
	{
		JointSessionBtn->SetIsEnabled(true);

		for (int NumChild = 0; NumChild < RootListPanel->GetChildrenCount(); NumChild++)
		{
			UWidget* Widget = RootListPanel->GetChildAt(NumChild);

			if (Widget != LineSelected)
			{
				Widget->SetIsEnabled(true);
			}
		}
	}
}