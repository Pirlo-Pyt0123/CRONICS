#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PlayerController.h"
#include "CRONICSPawn.generated.h"

UCLASS(Blueprintable)
class ACRONICSPawn : public APawn
{
    GENERATED_BODY()

    UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* ShipMeshComponent;

    /** The camera */
    UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* CameraComponent;

    /** Camera boom positioning the camera above the character */
    UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    // Para el componente de colisión
    UPROPERTY(EditAnywhere, Category = "Componentes")
    class UBoxComponent* Colision_Pawn;



public:

    ACRONICSPawn();

    /** Offset from the ships location to spawn projectiles */
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
    FVector GunOffset;

    /* How fast the weapon will fire */
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
    float FireRate;

    /* The speed our ship moves around the level */
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
    float MoveSpeed;

    /** Sound to play each time we fire */
    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
    class USoundBase* FireSound;

    //sonido de seleccion de estrategia 
    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
    class USoundBase* SelectSound;

    //sonido de la aceleracion
    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
    class USoundBase* AccelerationSound;


    // Declare the particle system component for the ship's thruster
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles")
    UParticleSystemComponent* Invulnerabilidad_Particle;

    // Declare the particle system components for the left and right side of the ship
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles")
    UParticleSystemComponent* ProyecAceLeft;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles")
    UParticleSystemComponent* ProyecAceRight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles")
    UParticleSystemComponent* AceRightA;

    // Declare the particle system components for the left and right side of the ship
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles")
    UParticleSystemComponent* AceLeftB;
   


    // Begin Actor Interface
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    // End Actor Interface

    // Static names for axis bindings
    static const FName MoveForwardBinding;
    static const FName MoveRightBinding;
    static const FName FireForwardBinding;
    static const FName FireRightBinding;
    static const FName FireUpBinding;

private:
    /* Flag to control firing  */
    uint32 bCanFire : 1;

    /** Handle for efficient management of ShotTimerExpired timer */
    FTimerHandle TimerHandle_ShotTimerExpired;
    // bool bIsAccelerating; // Si la nave está acelerando

    float CurrentStrafeSpeed; // Velocidad lateral (para movimiento en Y)
    float CurrentVerticalSpeed; // Velocidad vertical (para movimiento en Z)

    float MinPitchAngle = -45.0f; // Ángulo mínimo de Pitch
    float MaxPitchAngle = 45.0f; // Ángulo máximo de Pitch
    float MinYawAngle = -180.0f; // Ángulo mínimo de Yaw
    float MaxYawAngle = 180.0f; // Ángulo máximo de Yaw



public:
    /** Returns ShipMeshComponent subobject **/
    FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
    /** Returns CameraComponent subobject **/
    FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

    UPROPERTY(Category = Plane, EditAnywhere)
    float Acceleration;

    /** How quickly pawn can steer */
    UPROPERTY(Category = Plane, EditAnywhere)
    float TurnSpeed;

    /** Max forward speed */
    UPROPERTY(Category = Pitch, EditAnywhere)
    float MaxSpeed;

    /** Min forward speed */
    UPROPERTY(Category = Yaw, EditAnywhere)
    float MinSpeed;

    /** Current forward speed */
    float CurrentForwardSpeed;

    /** Current yaw speed */
    float CurrentYawSpeed;

    /** Current pitch speed */
    float CurrentPitchSpeed;

    /** Current roll speed */
    float CurrentRollSpeed;

    float CurrentAcceleration;

    void ThrustInput(float Val);
    /** Bound to the vertical axis */
    void MoveUpInput(float Val);
    /** Bound to the horizontal axis */
    void MoveRightInput(float Val);

public:

    bool bIsLookingBack;

    //PRIMER VELOCIDAD
    void StartAccelerating();
    void StopAccelerating();


public:

    float Damage_A;
    float Life;
    float MaxLife;

    int32 CurrentLives;
    int32 CurrentTerraBley;

    float Standard_Speed;
    float Increased_Speed;
    float Ultra_Increased_Speed;


    bool bIsSuperAccelerating;
    float SuperAccelerationPower;
    FVector SuperAcceleratedCameraLocation;

private:

    UAudioComponent* AccelerationAudioComponent;
    bool bIsAccelerating;
    float DefaultAcceleration;
    float MaxeSpeed;
    float MineSpeed;

    FVector OriginalCameraLocation;
    FVector AcceleratedCameraLocation;

    float CurrentSpeedProgress;
    float SpeedRegenRate;
    float SpeedDepleteRate;
    bool bIsSpeedDepleting;

    bool bCanAccelerate;
    bool bCanSuperAccelerate;


};