// Fill out your copyright notice in the Description page of Project Settings.


#include "B_Kepler22B.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "CRONICSPawn.h"
#include "DialogoActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"

AB_Kepler22B::AB_Kepler22B()
{
	//tick is disabled
	PrimaryActorTick.bCanEverTick = false;



	// Initialize the rotation speed
	RotationSpeed = 20.f;  // Default value, adjustable in the editor

	// Set the mesh to the planet
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlanetMeshAsset(TEXT("StaticMesh'/Game/Proxima_b_1_13776/prkl.prkl'"));
	if (PlanetMeshAsset.Succeeded())
	{
		PlanetMesh->SetStaticMesh(PlanetMeshAsset.Object);
		PlanetMesh->SetRelativeScale3D(FVector(250.5f, 250.0f, 250.0f));

	}

	// Audio component
	AudioKepler = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioKepler->SetupAttachment(RootComponent);
	AudioKepler->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("SoundWave'/Game/sound/12.12'"));
	if (SoundAsset.Succeeded())
	{
		AudioKepler->SetSound(SoundAsset.Object);

	}



}

void AB_Kepler22B::BeginPlay()
{
	Super::BeginPlay();

	// Here you can add start logic if necessary
}

void AB_Kepler22B::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Make the planet rotate constantly
	FRotator Rotation = FRotator(0.f, RotationSpeed * DeltaTime, 0.f);
	AddActorLocalRotation(Rotation);

}

void AB_Kepler22B::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("The player has interacted with the exoplanet."));
	// This function can be overridden to create specific interactions
}

void AB_Kepler22B::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Verificar si el otro actor es la nave del jugador
	ACRONICSPawn* PlayerPawn = Cast<ACRONICSPawn>(OtherActor);
	if (PlayerPawn)
	{
		// Spawnear el DialogoActor y mostrar el texto específico de este planeta
		ADialogoActor* Dialogo = GetWorld()->SpawnActor<ADialogoActor>();
		if (Dialogo)
		{
			Dialogo->MostrarDialogo(FText::FromString("Has llegado a un exoplaneta."));
			AudioKepler->Play();
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Has llegado a un exoplaneta."));
	}
}

