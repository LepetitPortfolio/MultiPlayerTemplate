// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/MPT_MainMenuLevel.h"
#include "System/MPT_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MPT_HUDSystem.h"

// Called when the game starts or when spawned
void AMPT_MainMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	UMPT_GameInstance* GameInstance = Cast<UMPT_GameInstance>(UGameplayStatics::GetGameInstance((const UObject*)GetWorld()));

	if (GameInstance)
	{
		AMPT_HUDSystem* HUD = UGameplayStatics::GetPlayerController((const UObject*)GetWorld(), 0)->GetHUD<AMPT_HUDSystem>();

		if (HUD)
		{
			HUD->OnGameStateChange(EGameStateType::MainMenu);
		}
	}
}

void AMPT_MainMenuLevel::Tick(float DeltaTime)
{
}
