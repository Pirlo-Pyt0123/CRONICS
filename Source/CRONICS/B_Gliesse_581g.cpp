// Fill out your copyright notice in the Description page of Project Settings.


#include "B_Gliesse_581g.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "CRONICSPawn.h"  // La nave del jugador
#include "DialogoActor.h"  // Actor de diálogo
#include "Components/BoxComponent.h"  // Componente de colisión
#include "Components/AudioComponent.h"
	

AB_Gliesse_581g::AB_Gliesse_581g()
{
	PrimaryActorTick.bCanEverTick = false;


	RotationSpeed = 20.f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlanetMeshAsset(TEXT("StaticMesh'/Game/Proxima_b_1_13776/prMesh.prMesh'"));
	if (PlanetMeshAsset.Succeeded())
	{
		PlanetMesh->SetStaticMesh(PlanetMeshAsset.Object);
		PlanetMesh->SetRelativeScale3D(FVector(310.5f, 310.0f, 310.0f));
	}

	// audio component
	AudioGliese = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioGliese->SetupAttachment(RootComponent);
	AudioGliese->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("SoundWave'/Game/sound/11.11'"));
	if (SoundAsset.Succeeded())
	{
		AudioGliese->SetSound(SoundAsset.Object);

	}


}

void AB_Gliesse_581g::BeginPlay()
{
	Super::BeginPlay();
}

void AB_Gliesse_581g::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotation = FRotator(0.f, RotationSpeed * DeltaTime, 0.f);
	AddActorLocalRotation(Rotation);
}

void AB_Gliesse_581g::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("The player has interacted with the exoplanet."));
}

void AB_Gliesse_581g::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Verificar si el otro actor es la nave del jugador
	ACRONICSPawn* PlayerPawn = Cast<ACRONICSPawn>(OtherActor);
	if (PlayerPawn)
	{
		// Spawnear el DialogoActor y mostrar el texto específico de este planeta
		ADialogoActor* Dialogo = GetWorld()->SpawnActor<ADialogoActor>();
		if (Dialogo)
		{
			Dialogo->MostrarDialogo(FText::FromString(
				"Bienvenido al planeta Gliesse\n"
				"el gigante gasesoso\n"
				"Gliesse 581g\n"
				"Muy alejado y gaseoso \n"));
			AudioGliese->Play();
		}
	}
}


