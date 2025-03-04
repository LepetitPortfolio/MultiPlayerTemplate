// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPT_InGameScreen.h"
#include "Components/ScaleBox.h"

void UMPT_InGameScreen::NativeConstruct()
{
	if (InGameMenu)
	{
		InGameMenu->SetVisibility(ESlateVisibility::Collapsed);
	}
}


void UMPT_InGameScreen::NativeDestruct()
{
}
