// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPT_MainMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MPT_HUDSystem.h"

void UMPT_MainMenu::NativeConstruct()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}

void UMPT_MainMenu::NativeDestruct()
{
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
}

void UMPT_MainMenu::OpenHostMenu()
{
	AMPT_HUDSystem* HUD = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD<AMPT_HUDSystem>();

	if (HUD)
	{
		HUD->OnGameStateChange(EGameStateType::HostMenu);
	}
}


void UMPT_MainMenu::OpenJoinMenu()
{
	AMPT_HUDSystem* HUD = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD<AMPT_HUDSystem>();

	if (HUD)
	{
		HUD->OnGameStateChange(EGameStateType::JointMenu);
	}
}

void UMPT_MainMenu::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}
