#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSSDialogoWidget.h"  // Incluir el widget personalizado
#include "DialogoActor.generated.h"

UCLASS()
class CRONICS_API ADialogoActor : public AActor
{
    GENERATED_BODY()

public:
    ADialogoActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Mostrar el diálogo en el widget
    void MostrarDialogo(const FText& LineaDeDialogo);
	void MostrarDialogo2(const FText& LineaDeDialogo);
	void MostrarDialogo3(const FText& LineaDeDialogo);
	void MostrarDialogo4(const FText& LineaDeDialogo);

public:
    // Widget de diálogo
    TSharedPtr<SSSDialogoWidget> DialogoWidget;

	float Time;
};
