// Fill out your copyright notice in the Description page of Project Settings.


#include "B_ProximaCentauriB.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "CRONICSPawn.h"
#include "DialogoActor.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"

AB_ProximaCentauriB::AB_ProximaCentauriB()
{
	PrimaryActorTick.bCanEverTick = false;


	RotationSpeed = 20.f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlanetMeshAsset(TEXT("StaticMesh'/Game/Proxima_b_1_13776/prMesh.prMesh'"));
	if (PlanetMeshAsset.Succeeded())
	{
		PlanetMesh->SetStaticMesh(PlanetMeshAsset.Object);
		PlanetMesh->SetRelativeScale3D(FVector(650.0f, 650.0f, 650.0f));
	}

	AudioCent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioCent->SetupAttachment(RootComponent);
	AudioCent->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("SoundWave'/Game/sound/21.21'"));
	if (SoundAsset.Succeeded())
	{
		AudioCent->SetSound(SoundAsset.Object);

	}

}

void AB_ProximaCentauriB::BeginPlay()
{

}

void AB_ProximaCentauriB::Tick(float DeltaTime)
{

}

void AB_ProximaCentauriB::Interact()
{
}

void AB_ProximaCentauriB::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
				"Bienvenido al planeta Proxima Centauri\n"
				"De las mas grandes y con mas capacidad te almacenar vida\n"
				"Muy alejado de todo tipo \n"));
			AudioCent->Play();
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Has llegado a un exoplaneta."));
	}
}
