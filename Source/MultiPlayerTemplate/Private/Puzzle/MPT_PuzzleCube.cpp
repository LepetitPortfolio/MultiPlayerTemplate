// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle/MPT_PuzzleCube.h"
#include "Characters/MPT_PuzzleCharacterExemple.h"

// Sets default values
AMPT_PuzzleCube::AMPT_PuzzleCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	m_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	
}

// Called when the game starts or when spawned
void AMPT_PuzzleCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPT_PuzzleCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMPT_PuzzleCube::Interact(AActor* _InteractingActor)
{
	AMPT_PuzzleCharacterExemple* puzzleCharacter = Cast<AMPT_PuzzleCharacterExemple>(_InteractingActor);

	if (puzzleCharacter)
	{
		m_StaticMesh->SetSimulatePhysics(false);

		FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(puzzleCharacter->GetCubeLocation(), attachmentRules, FName("PuzzleCube"));
	}
}

