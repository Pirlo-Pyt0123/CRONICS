// Fill out your copyright notice in the Description page of Project Settings.


#include "B_Trappist_1e.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "CRONICSPawn.h"
#include "DialogoActor.h"
#include "Components/BoxComponent.h"



AB_Trappist_1e::AB_Trappist_1e()
{
	//tick 
	PrimaryActorTick.bCanEverTick = true;

		
	//rotation speed
	RotationSpeed = 20.f;

	//mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlanetMeshAsset(TEXT("StaticMesh'/Game/trappis/MarsPlanet/MarsPlanet.MarsPlanet'"));
	if (PlanetMeshAsset.Succeeded())
	{
		PlanetMesh->SetStaticMesh(PlanetMeshAsset.Object);
		PlanetMesh->SetRelativeScale3D(FVector(150.5f, 150.0f, 150.0f));

	}
	
	

}

void AB_Trappist_1e::BeginPlay()
{
	Super::BeginPlay();

	//start logic
}

void AB_Trappist_1e::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//rotation
	FRotator Rotation = FRotator(0.f, RotationSpeed * DeltaTime, 0.f);
	AddActorLocalRotation(Rotation);


}

void AB_Trappist_1e::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("The player has interacted with the exoplanet."));
	//interaction
}

void AB_Trappist_1e::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

