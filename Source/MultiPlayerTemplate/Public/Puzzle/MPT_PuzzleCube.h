// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MPT_Interactable.h"
#include "Components/StaticMeshComponent.h"
#include "MPT_PuzzleCube.generated.h"

UCLASS()
class MULTIPLAYERTEMPLATE_API AMPT_PuzzleCube : public AActor, public IMPT_Interactable
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USceneComponent* m_CubeLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_StaticMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AMPT_PuzzleCube();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* _InteractingActor) override;

};
