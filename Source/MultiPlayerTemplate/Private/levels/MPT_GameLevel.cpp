// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/MPT_GameLevel.h"
#include "System/MPT_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MPT_HUDSystem.h"

void AMPT_GameLevel::BeginPlay()
{
	Super::BeginPlay();

	UMPT_GameInstance* GameInstance = Cast<UMPT_GameInstance>(UGameplayStatics::GetGameInstance((const UObject*)GetWorld()));

	if (GameInstance)
	{
		AMPT_HUDSystem* HUD = UGameplayStatics::GetPlayerController((const UObject*)GetWorld(), 0)->GetHUD<AMPT_HUDSystem>();

		if (HUD)
		{
			HUD->OnGameStateChange(EGameStateType::InGame);
		}
	}
}