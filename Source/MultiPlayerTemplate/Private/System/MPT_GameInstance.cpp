// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MPT_GameInstance.h"

UMPT_GameInstance::UMPT_GameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UMPT_GameInstance::Init()
{
	Super::Init();
	NetworkSystem =NewObject<AMPT_GameSession>();

	if (NetworkSystem)
	{
		NetworkSystem->SetGameInstance(this);
	}
}
