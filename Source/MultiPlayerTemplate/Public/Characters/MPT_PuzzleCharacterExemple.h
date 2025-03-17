// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MPT_BaseCharacter.h"
#include "Components/SceneComponent.h"
#include "MPT_PuzzleCharacterExemple.generated.h"


class UInputAction;

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API AMPT_PuzzleCharacterExemple : public AMPT_BaseCharacter
{
	GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* ActionInput;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PuzzleCharacterExemple, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* m_CubeLocation;

    /**
    * 
    */
    void TryInteract();

    /**
     * Server-side function to handle interactions with objects in the game world.
     * No parameters.
     */
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerInteract(AActor* _TargetActor);
    void ServerInteract_Implementation(AActor* _TargetActor);
    bool ServerInteract_Validate(AActor* _TargetActor);

public :

    AMPT_PuzzleCharacterExemple();

    inline class USceneComponent* GetCubeLocation() { return m_CubeLocation; }


    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
