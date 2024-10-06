#include "CRONICSGameMode.h"
#include "CRONICSPawn.h"
#include "A_Exoplanetas.h"
#include "B_ProximaCentauriB.h"
#include "B_Gliesse_581g.h"
#include "B_Kepler22B.h"
#include "B_Trappist_1e.h"
#include "DialogoActor.h"
#include "SUN.h"

ACRONICSGameMode::ACRONICSGameMode()
{
    // Set default pawn class to our character class
    DefaultPawnClass = ACRONICSPawn::StaticClass();
}

void ACRONICSGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Crear y posicionar los planetas
   
    AA_Exoplanetas* Planeta = GetWorld()->SpawnActor<AA_Exoplanetas>(AB_Trappist_1e::StaticClass(), FVector(113430.0 * 4, -950.0 * 2, -130.0), FRotator(0, 0, 0));
    AA_Exoplanetas* Planeta2 = GetWorld()->SpawnActor<AA_Exoplanetas>(AB_Gliesse_581g::StaticClass(), FVector(-17657.859375 * 8, 69993.617188 * 4, 38046.5), FRotator(0, 0, 0));
    AA_Exoplanetas* Planeta3 = GetWorld()->SpawnActor<AA_Exoplanetas>(AB_Kepler22B::StaticClass(), FVector(17657.859375 * 4, -69993.617188 * 2, 38046.5), FRotator(0, 0, 0));
	AA_Exoplanetas* Pleneta4 = GetWorld()->SpawnActor<AA_Exoplanetas>(AB_ProximaCentauriB::StaticClass(), FVector(53430.0 * 8, -250000.0 * 6, -450.0), FRotator(0, 0, 0));

	ASUN* Sol = GetWorld()->SpawnActor<ASUN>(ASUN::StaticClass(), FVector(17657.859375 * 8, -89993.617188 * 2, 45046.5), FRotator(0, 0, 0));
}

void ACRONICSGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
