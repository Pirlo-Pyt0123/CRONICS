#include "DialogoActor.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "A_Exoplanetas.h"
//planetas
#include "B_ProximaCentauriB.h"
#include "B_Gliesse_581g.h"
#include "B_Kepler22B.h"
#include "B_Trappist_1e.h"

ADialogoActor::ADialogoActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADialogoActor::BeginPlay()
{
    Super::BeginPlay();

    // Crear el widget de diálogo
    SAssignNew(DialogoWidget, SSSDialogoWidget)
        .DialogoTexto(FText::FromString("Texto Inicial"));

    if (GEngine && GEngine->GameViewport)
    {
        GEngine->GameViewport->AddViewportWidgetContent(
            SNew(SWeakWidget).PossiblyNullContent(DialogoWidget.ToSharedRef())
        );
    }
    MostrarDialogo(FText::FromString("Bienvenido al sistema planetario!\n"
        "Estos son los planetas que puedes explorar:\n"
        "1. Proxima Centauri B\n"
        "2. Gliesse 581g\n"
        "3. Kepler-22B\n"));
}

void ADialogoActor::MostrarDialogo(const FText& LineaDeDialogo)
{
    if (DialogoWidget.IsValid())
    {
        DialogoWidget->ActualizarTexto(LineaDeDialogo);
    }
}

void ADialogoActor::MostrarDialogo2(const FText& LineaDeDialogo)
{
    if (DialogoWidget.IsValid())
    {
        DialogoWidget->ActualizarTexto(LineaDeDialogo);
    }
}

void ADialogoActor::MostrarDialogo3(const FText& LineaDeDialogo)
{
    if (DialogoWidget.IsValid())
    {
        DialogoWidget->ActualizarTexto(LineaDeDialogo);
    }
}

void ADialogoActor::MostrarDialogo4(const FText& LineaDeDialogo)
{
    if (DialogoWidget.IsValid())
    {
        DialogoWidget->ActualizarTexto(LineaDeDialogo);
    }
}




void ADialogoActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
	Time = DeltaTime;
	if (Time >= 5.0f)
		
	{
			// Mostrar el diálogo
			MostrarDialogo(FText::FromString("¡Bienvenido al sistema planetario!"));

			Time = 0.0f;

            
           
	}
    


    
}

