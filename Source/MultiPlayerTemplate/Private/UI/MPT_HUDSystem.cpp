// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPT_HUDSystem.h"

#include "Blueprint/UserWidget.h"

void AMPT_HUDSystem::BeginPlay()
{

}


void AMPT_HUDSystem::OnGameStateChange(EGameStateType NewState)
{
	UUserWidget* NewWidget = InstatiateUserWidget(NewState);

	if (NewWidget)
	{
		DisplayWidget(NewWidget);
	}
}

UUserWidget* AMPT_HUDSystem::InstatiateUserWidget(EGameStateType NewState)
{
	if (!UIByGameStep.Contains(NewState))
	{
		return nullptr;
	}

	return CreateWidget<UUserWidget>(GetWorld(), UIByGameStep[NewState]);
}

void AMPT_HUDSystem::DisplayWidget(UUserWidget* NewWidget)
{
	if (!NewWidget)
	{
		return;
	}

	if (ActiveUI)
	{
		ActiveUI->RemoveFromViewport();
	}

	ActiveUI = NewWidget;
	ActiveUI->AddToViewport();
}
