// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPT_HostMenu.h"
#include "System/MPT_GameInstance.h"
#include "UI/MPT_HUDSystem.h"
#include "Kismet/GameplayStatics.h"
#include "System/MPT_GameSession.h"

void UMPT_HostMenu::NativeConstruct()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	UMPT_GameInstance* GameInstance = Cast<UMPT_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->GetLevelInfos()->GetAllRows<FMPT_LevelInfos>("", MapList);
		MapIndex = 0;
		MapInfosSelected = MapList[MapIndex];
		MapName = MapInfosSelected->LevelName.ToString();
	}

	PlayersMax = 4;
}

void UMPT_HostMenu::NativeDestruct()
{
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
}

void UMPT_HostMenu::MorePlayer()
{
	PlayersMax++;
	if (PlayersMax > 4)
	{
		PlayersMax = 4;
	}
}

void UMPT_HostMenu::LessPlayer()
{
	PlayersMax--;
	if (PlayersMax < 2)
	{
		PlayersMax = 2;
	}
}

void UMPT_HostMenu::NextMap()
{
	MapIndex++;
	if (MapIndex >= MapList.Num())
	{
		MapIndex = 0;
	}

	MapInfosSelected = MapList[MapIndex];
	MapName = MapInfosSelected->LevelName.ToString();
}

void UMPT_HostMenu::PreviousMap()
{
	MapIndex--;
	if (MapIndex < 0)
	{
		MapIndex = MapList.Num() - 1;
	}
	MapInfosSelected = MapList[MapIndex];
	MapName = MapInfosSelected->LevelName.ToString();
}

void UMPT_HostMenu::Return()
{
	AMPT_HUDSystem* HUD =UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD<AMPT_HUDSystem>();

	if (HUD)
	{
		HUD->OnGameStateChange(EGameStateType::MainMenu);
	}
}

void UMPT_HostMenu::CreateHost()
{
	const ULocalPlayer* Player = GetGameInstance<UMPT_GameInstance>()->GetFirstGamePlayer();

	FString LevelName = MapInfosSelected->Level.GetAssetName();

	FUniqueNetIdRepl unr = Player->GetPreferredUniqueNetId();

	FUniqueNetIdPtr userID = unr.GetUniqueNetId();

	//FUniqueNetId uID = Player->GetPreferredUniqueNetId().GetUniqueNetId();

	GetGameInstance<UMPT_GameInstance>()->GetNetworkSystem()->HostSession(GetWorld(), Player->GetPreferredUniqueNetId().GetUniqueNetId(), SessionName, LevelName, IsLAN, IsPresence, PlayersMax);
}
