#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "A_Exoplanetas.generated.h"

UCLASS()
class CRONICS_API AA_Exoplanetas : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AA_Exoplanetas();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // Componente de malla estática (para la visualización del planeta)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* PlanetMesh;

    // Componente de colisión esférica (para la detección de colisiones)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBoxComponent* Colision_e;

    // Velocidad de rotación del planeta
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Properties")
    float RotationSpeed;

    // Función para manejar la interacción con el planeta (puede sobrescribirse en planetas derivados)
    UFUNCTION(BlueprintCallable, Category = "Planet")
    virtual void Interact();

    UFUNCTION()
    virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
