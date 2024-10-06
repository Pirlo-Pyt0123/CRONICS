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

    // Componente de malla est�tica (para la visualizaci�n del planeta)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* PlanetMesh;

    // Componente de colisi�n esf�rica (para la detecci�n de colisiones)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBoxComponent* Colision_e;

    // Velocidad de rotaci�n del planeta
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Properties")
    float RotationSpeed;

    // Funci�n para manejar la interacci�n con el planeta (puede sobrescribirse en planetas derivados)
    UFUNCTION(BlueprintCallable, Category = "Planet")
    virtual void Interact();

    UFUNCTION()
    virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
