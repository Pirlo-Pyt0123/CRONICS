// Fill out your copyright notice in the Description page of Project Settings.


#include "SUN.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASUN::ASUN()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Meshes/SunMesh.SunMesh'"));
	if (MeshAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshAsset.Object);
		MeshComp->SetRelativeScale3D(FVector(50.0f, 50.0f, 50.0f));

	}



}

// Called when the game starts or when spawned
void ASUN::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASUN::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

