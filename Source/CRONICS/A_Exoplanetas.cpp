#include "A_Exoplanetas.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "CRONICSPawn.h"	
#include "DialogoActor.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AA_Exoplanetas::AA_Exoplanetas()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Crear el componente de malla estática para representar el planeta
	PlanetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMesh"));
	RootComponent = PlanetMesh;  // Establecer como raíz del actor

	Colision_e = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision_Pawn"));
	Colision_e->SetCollisionProfileName(TEXT("Pawn"));
	Colision_e = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision_Planeta"));
	Colision_e->SetupAttachment(PlanetMesh);  // Se adjunta al componente de malla del planeta

	Colision_e->SetBoxExtent(FVector(60.f, 60.f, 60.f));
	Colision_e->OnComponentBeginOverlap.AddDynamic(this, &AA_Exoplanetas::OnOverlapBegin);
	Colision_e->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	

	// Inicializar la velocidad de rotación
	RotationSpeed = 20.f;  // Valor por defecto, ajustable en el editor
}

// Called when the game starts or when spawned
void AA_Exoplanetas::BeginPlay()
{
	Super::BeginPlay();

	// Aquí puedes agregar lógica de inicio si es necesario
}

// Called every frame
void AA_Exoplanetas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Hacer que el planeta rote constantemente
	FRotator Rotation = FRotator(0.f, RotationSpeed * DeltaTime, 0.f);
	AddActorLocalRotation(Rotation);
}

// Función de interacción (virtual para sobrescribir en clases derivadas)
void AA_Exoplanetas::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("El jugador ha interactuado con el exoplaneta."));
	// Esta función se puede sobrescribir para crear interacciones específicas
}

void AA_Exoplanetas::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

