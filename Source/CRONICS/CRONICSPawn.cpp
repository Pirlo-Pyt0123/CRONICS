#include "CRONICSPawn.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/CollisionProfile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"


const FName ACRONICSPawn::MoveForwardBinding("MoveForward");
const FName ACRONICSPawn::MoveRightBinding("MoveRight");
const FName ACRONICSPawn::FireForwardBinding("FireForward");
const FName ACRONICSPawn::FireRightBinding("FireRight");
const FName ACRONICSPawn::FireUpBinding("FireUp");

ACRONICSPawn::ACRONICSPawn()
{
	PrimaryActorTick.bCanEverTick = true;


	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/b1/source/blue.blue'"));
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	if (ShipMesh.Succeeded())
	{
		ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
		ShipMeshComponent->SetWorldScale3D(FVector(0.10f, 0.10f, 0.10f));
		
	}

	// Crear y configurar el CameraBoom para que esté detrás de la nave
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	CameraBoom->SetupAttachment(RootComponent); // Adjuntar el CameraBoom al RootComponent (la nave)
	CameraBoom->TargetArmLength = 400.0f; // Distancia de la cámara detrás de la nave
	CameraBoom->SocketOffset = FVector(-900.0f, 0.f, 600.f); // Ajustar la posición de la cámara detrás de la nave
	CameraBoom->bEnableCameraLag = true; // Habilitar el lag de la cámara para suavizar el movimiento
	CameraBoom->CameraLagSpeed = 3.f; // Ajustar la velocidad del lag de la cámara para que siga suavemente

	// Crear y configurar la cámara para que esté siempre detrás de la nave
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // La cámara no rota con el control del jugador

	// Ajustar la posición de inicio de la cámara
	OriginalCameraLocation = CameraBoom->SocketOffset;
	AcceleratedCameraLocation = FVector(-450.f, 0.f, 200.f); // Ajusta la posición detrás de la nave


	// Crear y configurar el componente de colisión
	Colision_Pawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision_Pawn"));
	Colision_Pawn->SetCollisionProfileName(TEXT("Pawn"));
	Colision_Pawn->SetupAttachment(RootComponent);

	Colision_Pawn->SetBoxExtent(FVector(1100.f, 500.f, 400.f));

	

	// Parámetros de manejo
	Acceleration = 8000.f;
	TurnSpeed = 50.f;

	MaxSpeed = 500.f;
	MinSpeed = 500.f;

	MoveSpeed = 500.0f;

	bIsAccelerating = false;
	DefaultAcceleration = 1000.0f;

	Standard_Speed = 1000.0f;
	Increased_Speed = 35000.0f;
	Ultra_Increased_Speed = 6000.0f;

	Acceleration = DefaultAcceleration;
	CurrentForwardSpeed = 15500.0f; // Velocidad inicial
	MaxeSpeed = 30500.0f; // Velocidad máxima
	MineSpeed = 500.0f; // Velocidad mínima

	// Inicializar variables
	bIsSuperAccelerating = false;
	SuperAccelerationPower = 30000.0f;
	SuperAcceleratedCameraLocation = FVector(-1000.f, 0.f, 700.f);

	CurrentSpeedProgress = 1.0f;
	SpeedRegenRate = 0.25f;
	SpeedDepleteRate = 0.05f;
	bIsSpeedDepleting = false;

	bCanAccelerate = true;
	bCanSuperAccelerate = true;

	// Configurar sistemas de partículas
	ProyecAceLeft = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AccelerationParticlesComponentLeft"));
	ProyecAceRight = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AccelerationParticlesComponentRight"));

	// Configurar los sistemas de partículas
	ProyecAceLeft->SetupAttachment(ShipMeshComponent);
	ProyecAceRight->SetupAttachment(ShipMeshComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> AccelerationParticlesAsset(TEXT("ParticleSystem'/Game/VFXSeries1/Particles/Energy/P_ChargedPlasma.P_ChargedPlasma'"));
	if (AccelerationParticlesAsset.Succeeded())
	{
		ProyecAceLeft->SetTemplate(AccelerationParticlesAsset.Object);
		ProyecAceLeft->bAutoActivate = false;
		ProyecAceLeft->SetWorldScale3D(FVector(30.0f, 30.0f, 30.0f));
		ProyecAceLeft->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		ProyecAceLeft->SetRelativeLocation(FVector(-3000.0f, -150.0f, 70.0f));

		ProyecAceRight->SetTemplate(AccelerationParticlesAsset.Object);
		ProyecAceRight->bAutoActivate = false;
		ProyecAceRight->SetWorldScale3D(FVector(30.0f, 30.0f, 30.0f));
		ProyecAceRight->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		ProyecAceRight->SetRelativeLocation(FVector(-3000.0f, 150.0f, 70.0f));
	}
	
}

void ACRONICSPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Control de aceleración y superaceleración
	if (bIsSuperAccelerating && bCanSuperAccelerate)
	{
		CurrentAcceleration = Ultra_Increased_Speed;
		MaxSpeed = Ultra_Increased_Speed;
		MinSpeed = Ultra_Increased_Speed / 2;
		bIsSpeedDepleting = true;
	}
	else if (bIsAccelerating && bCanAccelerate)
	{
		CurrentAcceleration = Increased_Speed;
		MaxSpeed = Increased_Speed;
		MinSpeed = Increased_Speed / 2;
		bIsSpeedDepleting = true;
	}
	else
	{
		CurrentAcceleration = Standard_Speed;
		MaxSpeed = Standard_Speed;
		MinSpeed = Standard_Speed;
		bIsSpeedDepleting = false;
	}

	// Actualizar la velocidad en función de la aceleración
	CurrentForwardSpeed += CurrentAcceleration * DeltaTime;
	CurrentForwardSpeed = FMath::Clamp(CurrentForwardSpeed, MinSpeed, MaxSpeed);

	// Movimiento basado en la velocidad actual
	FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, 0.f, 0.f);
	AddActorLocalOffset(LocalMove, true);

	// **Aplicar rotación local a la nave (ejes Yaw, Pitch y Roll)**
	FRotator DeltaRotation(0.f, 0.f, 0.f);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaTime;
	AddActorLocalRotation(DeltaRotation);

	// Movimiento en los ejes Y y Z (para movimientos laterales y verticales)
	FVector StrafeMove = FVector(0.f, CurrentStrafeSpeed * DeltaTime, CurrentVerticalSpeed * DeltaTime);
	AddActorLocalOffset(StrafeMove, true);

	//// **Interpolación de la ubicación de la cámara**
	//FVector TargetCameraLocation = bIsAccelerating ? AcceleratedCameraLocation : OriginalCameraLocation;
	//CameraBoom->SocketOffset = FMath::VInterpTo(CameraBoom->SocketOffset, TargetCameraLocation, DeltaTime, 5.f);
}

	
void ACRONICSPawn::BeginPlay()
{
	Super::BeginPlay();

}

void ACRONICSPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Verificar el componente de entrada
	check(PlayerInputComponent);

	// Enlazar los ejes de movimiento
	PlayerInputComponent->BindAxis("Thrust", this, &ACRONICSPawn::ThrustInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &ACRONICSPawn::MoveUpInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACRONICSPawn::MoveRightInput);

	// Enlazar acciones de aceleración
	PlayerInputComponent->BindAction("Accelerate", IE_Pressed, this, &ACRONICSPawn::StartAccelerating);
	PlayerInputComponent->BindAction("Accelerate", IE_Released, this, &ACRONICSPawn::StopAccelerating);


}

void ACRONICSPawn::ThrustInput(float Val)
{
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	float CurrentAcc = bHasInput ? (Val * Acceleration) : (-0.5f * Acceleration); // Si no hay entrada, desacelerar
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);

	// Ajuste suave de la velocidad
	if (!bHasInput)
	{
		NewForwardSpeed = FMath::FInterpTo(CurrentForwardSpeed, MinSpeed, GetWorld()->GetDeltaSeconds(), 0.5f); // Inercia
	}

	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
}

void ACRONICSPawn::MoveUpInput(float Val)
{
	// Rotación en el eje Pitch (arriba/abajo)
	float TargetPitchSpeed = Val * TurnSpeed * -1.f;
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}


void ACRONICSPawn::MoveRightInput(float Val)
{
	// Rotación en el eje Yaw (izquierda/derecha)
	float TargetYawSpeed = Val * TurnSpeed;
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// Ajustar el Roll en función del giro
	const bool bIsTurning = FMath::Abs(Val) > 0.2f;
	float TargetRollSpeed = bIsTurning ? (Val * -10.0f) : (GetActorRotation().Roll * -2.f);
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ACRONICSPawn::StartAccelerating()
{
	if (bCanAccelerate && CurrentSpeedProgress > 0.0f)
	{
		bIsAccelerating = true;
		
		ProyecAceLeft->Activate();
		ProyecAceRight->Activate();

		
	}
	else
	{
		bIsAccelerating = false;
		//Desactivar la particula de aceleracion
		ProyecAceLeft->Deactivate();
		ProyecAceRight->Deactivate();
	}
	
}

void ACRONICSPawn::StopAccelerating()
{
	bIsAccelerating = false;
	
	ProyecAceLeft->Deactivate();
	ProyecAceRight->Deactivate();
}
