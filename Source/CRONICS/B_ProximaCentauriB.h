// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_Exoplanetas.h"
#include "B_ProximaCentauriB.generated.h"

/**
 * 
 */
UCLASS()
class CRONICS_API AB_ProximaCentauriB : public AA_Exoplanetas
{
	GENERATED_BODY()
public:
	AB_ProximaCentauriB();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to handle the interaction with the planet (can be overridden in derived planets)
	virtual void Interact() override;

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;

	//audio component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UAudioComponent* AudioCent;

};
