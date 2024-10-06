// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_Exoplanetas.h"
#include "B_Kepler22B.generated.h"

/**
 * 
 */
UCLASS()
class CRONICS_API AB_Kepler22B : public AA_Exoplanetas
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AB_Kepler22B();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Función para manejar la interacción con el planeta (puede sobrescribirse en planetas derivados)
	virtual void Interact() override;
		

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;

	//audio component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UAudioComponent* AudioKepler;
};
