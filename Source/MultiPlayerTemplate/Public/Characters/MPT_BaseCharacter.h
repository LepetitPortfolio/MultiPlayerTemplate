#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Enums/MPT_CharacterVueType.h"
#include "MPT_BaseCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBaseCharacter, Log, All);

class UInputAction;
struct FInputActionValue;


UCLASS(config = Game)
class MULTIPLAYERTEMPLATE_API AMPT_BaseCharacter : public ACharacter
{
    GENERATED_BODY()


protected:

    /** Spring arm component for third-person camera. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* ThirdPersonSpringArm;

    /** Camera component for third-person view. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* ThirdPersonCamera;

    /** Camera component for first-person view. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FirstPersonCamera;

    /** Skeletal mesh component for first-person arms. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
    USkeletalMeshComponent* FirstPersonMesh;

    /** Jump Input Action */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* FireInput;

    /** Move Input Action */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* LookAction;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* ZoomAction;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* SprintAction;

    /**
     * Replicated health variable that stores the character's current health points.
     */
    //UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Health")
    //float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    ECharacterVueType m_CharacterVueTypeSetting = ECharacterVueType::FTPS;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    float m_ArmLengthMax = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    float m_ArmLengthMin = 100.0f;
   
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    float m_DefaultSpeedCoef = 1.0f;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    float m_SprintSpeedCoef = 2.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    float m_CurrentSpeedCoef = 1.0f;

    /** Boolean flag indicating whether the character is currently in first-person view. */
    bool bIsFirstPerson;

    virtual void BeginPlay() override;

    void InitializeCameraTypeMode();

    /**
     * Handles character movement forward and backward.
     * @param Value Movement input value (positive for forward, negative for backward).
     */
    void Move(const FInputActionValue& Value);

    void TPSMove(const FInputActionValue& Value);

    void FPSMove(const FInputActionValue& Value);


    /** 
    * Called for looking input 
    */
    void Look(const FInputActionValue& Value);

    /**
    * Called for looking input
    */
    UFUNCTION()
    void ZoomCamera(const FInputActionValue& Value);

    void SwitchCameraPointOfView(bool _IsFirstPerson, bool _ForceSwitch = false);

    /** Initiates the character jump action when the jump key is pressed. */
    void StartJump();

    /** Stops the character jump action when the jump key is released. */
    void StopJump();

    /** 
    * 
    */
    void StartSprint();

    /**
    *
    */
    void StopSprint();


    /**
     * Server-side function to handle firing logic, ensuring synchronization in multiplayer.
     * No parameters.
     */
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerFire();
    void ServerFire_Implementation();
    bool ServerFire_Validate();
    

    /** Updates health and checks if the character should be destroyed upon depletion. */
    UFUNCTION()
    void OnHealthUpdate();

    /**
     * Handles applying damage to the character on the server and updating health accordingly.
     * @param DamageAmount The amount of damage to apply.
     */
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerTakeDamage(float DamageAmount);
    void ServerTakeDamage_Implementation(float DamageAmount);
    bool ServerTakeDamage_Validate(float DamageAmount);
   

public:
    AMPT_BaseCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
