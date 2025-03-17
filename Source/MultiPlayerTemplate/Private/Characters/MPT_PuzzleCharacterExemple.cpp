// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MPT_PuzzleCharacterExemple.h"
#include "Puzzle/MPT_Interactable.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AMPT_PuzzleCharacterExemple::TryInteract()
{
    FVector start = GetActorLocation();
    FVector forwardVector = GetControlRotation().Vector();
    FVector end = start + forwardVector * 200.f;

    FHitResult hitResult;
    FCollisionQueryParams params;

    AActor* interactableActor = nullptr;

    params.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, params))
    {
        AActor* hitActor = hitResult.GetActor();
        if ((hitActor) && (hitActor->Implements<UMPT_Interactable>()))
        {
            interactableActor = hitActor;
        }
    }

    ServerInteract(interactableActor);

}

void AMPT_PuzzleCharacterExemple::ServerInteract_Implementation(AActor* _TargetActor)
{
    if (_TargetActor && _TargetActor->Implements<UMPT_Interactable>())
    {
        IMPT_Interactable* interactable = Cast<IMPT_Interactable>(_TargetActor);
        if (interactable)
        {
            interactable->Interact(this);
        }
    }
}

bool AMPT_PuzzleCharacterExemple::ServerInteract_Validate(AActor* _TargetActor)
{
    return true;
}

AMPT_PuzzleCharacterExemple::AMPT_PuzzleCharacterExemple()
{
    m_CubeLocation = CreateDefaultSubobject<USceneComponent>(TEXT("CubeLocation"));
    m_CubeLocation->SetupAttachment(RootComponent);
    m_CubeLocation->SetRelativeLocation(FVector(100.0, 0.0f, 0.0f));
}

void AMPT_PuzzleCharacterExemple::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        enhancedInputComponent->BindAction(ActionInput, ETriggerEvent::Started, this, &AMPT_PuzzleCharacterExemple::TryInteract);

    }
    else
    {
        UE_LOG(LogBaseCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
    }
}
