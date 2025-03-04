#include "Characters/MPT_BaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

DEFINE_LOG_CATEGORY(LogBaseCharacter);

AMPT_BaseCharacter::AMPT_BaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bIsFirstPerson = true;

    ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArm"));
    ThirdPersonSpringArm->SetupAttachment(RootComponent);
    ThirdPersonSpringArm->TargetArmLength = m_ArmLengthMin;
    ThirdPersonSpringArm->bUsePawnControlRotation = true;

    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
    ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm);

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(RootComponent);

    FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    FirstPersonMesh->SetupAttachment(FirstPersonCamera);
    FirstPersonMesh->SetOnlyOwnerSee(true);

    Health = 100.0f;
}

void AMPT_BaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    SwitchCameraPointOfView(bIsFirstPerson);
    
}

void AMPT_BaseCharacter::Move(const FInputActionValue& Value)
{
    FVector2D movementVector = Value.Get<FVector2D>();
    if (Controller)
    {
        AddMovementInput(GetActorForwardVector() * m_CurrentSpeedCoef, movementVector.Y);
        AddMovementInput(GetActorRightVector() * m_CurrentSpeedCoef, movementVector.X);
    }
}


void AMPT_BaseCharacter::Look(const FInputActionValue& Value)
{
    FVector2D lookAxisVector = Value.Get<FVector2D>();
    if (Controller)
    {
        AddControllerYawInput(lookAxisVector.Y);
        AddControllerPitchInput(lookAxisVector.X);
    }
}

void AMPT_BaseCharacter::ZoomCamera(const FInputActionValue& Value)
{
    float zoomCamera = Value.Get<float>();
    if (Controller)
    {
        if ((bIsFirstPerson) && (zoomCamera > 0.0))
        {
            SwitchCameraPointOfView(false);
        }
        else
        {
            bool changeLengthArm = true;

            if ((ThirdPersonSpringArm->TargetArmLength == m_ArmLengthMin) && (zoomCamera < 0.0))
            {
                changeLengthArm = false;
            }

            if (changeLengthArm)
            {
                ThirdPersonSpringArm->TargetArmLength = FMath::Clamp(ThirdPersonSpringArm->TargetArmLength - zoomCamera * 10.0f, m_ArmLengthMin, m_ArmLengthMax);
            }
            else
            {
                SwitchCameraPointOfView(true);
            }

        }
    }
}

void AMPT_BaseCharacter::SwitchCameraPointOfView(bool _IsFirstPerson)
{
    bIsFirstPerson = _IsFirstPerson;
    FirstPersonCamera->SetActive(bIsFirstPerson);
    FirstPersonMesh->SetOwnerNoSee(!bIsFirstPerson);
    ThirdPersonCamera->SetActive(!bIsFirstPerson);
    GetMesh()->SetOwnerNoSee(bIsFirstPerson);

}

void AMPT_BaseCharacter::StartJump()
{
    Jump();
}

void AMPT_BaseCharacter::StopJump()
{
    StopJumping();
}

void AMPT_BaseCharacter::StartSprint()
{
    m_CurrentSpeedCoef = m_SprintSpeedCoef;
}

void AMPT_BaseCharacter::StopSprint()
{
    m_CurrentSpeedCoef = m_DefaultSpeedCoef;
}


void AMPT_BaseCharacter::ServerFire_Implementation()
{
    // Logic to handle firing a weapon
}

bool AMPT_BaseCharacter::ServerFire_Validate()
{
    return true;
}

void AMPT_BaseCharacter::ServerInteract_Implementation()
{
    // Logic to interact with objects
}

bool AMPT_BaseCharacter::ServerInteract_Validate()
{
    return true;
}

void AMPT_BaseCharacter::ServerTakeDamage_Implementation(float DamageAmount)
{
    Health = FMath::Clamp(Health - DamageAmount, 0.0f, 100.0f);
    OnHealthUpdate();
}

bool AMPT_BaseCharacter::ServerTakeDamage_Validate(float DamageAmount)
{
    return DamageAmount > 0.0f;
}

void AMPT_BaseCharacter::OnHealthUpdate()
{
    if (Health <= 0.0f)
    {
        Destroy();
    }
}

void AMPT_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMPT_BaseCharacter::StartJump);
        enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMPT_BaseCharacter::StopJump);

        enhancedInputComponent->BindAction(ActionInput, ETriggerEvent::Started, this, &AMPT_BaseCharacter::ServerInteract);
        //enhancedInputComponent->BindAction(FireInput, ETriggerEvent::Triggered, this, &AMPT_BaseCharacter::ServerFire);

        enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMPT_BaseCharacter::Move);

        enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMPT_BaseCharacter::Look);
        
        enhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AMPT_BaseCharacter::ZoomCamera);

        enhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMPT_BaseCharacter::StartSprint);
        enhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMPT_BaseCharacter::StopSprint);

    }
    else
    {
        UE_LOG(LogBaseCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
    }


}

void AMPT_BaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMPT_BaseCharacter, Health);
}
