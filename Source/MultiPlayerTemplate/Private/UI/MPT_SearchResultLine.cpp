// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPT_SearchResultLine.h"
#include "Online.h"
#include "UI/MPT_JointMenu.h"

void UMPT_SearchResultLine::InitValues(class UMPT_JointMenu* NewJointMenu, FOnlineSessionSearchResult* SessionSearchResultInfos)
{
	if (SessionSearchResultInfos)
	{
		SessionName = SessionSearchResultInfos->Session.SessionSettings.Settings.FindRef("SESSION_NAME").Data.ToString();

		PlayerConnected = 0;
		MaxPlayer = SessionSearchResultInfos->Session.NumOpenPublicConnections;

		SessionInfos.SessionName = FName(SessionName);
		SessionInfos.SessionSearchResult = SessionSearchResultInfos;
	}

	JointMenu = NewJointMenu;

}

void UMPT_SearchResultLine::OnClickAction()
{
	if (JointMenu)
	{
		SetIsEnabled(false);
		JointMenu->SetSessionSelected(this, &SessionInfos);
	}
}
