// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeDMIMod.h"
#include "firstperson415Character.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create comp and mesh subobjects
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");

	// Setup/Attach
	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
	Super::BeginPlay();

	// On Overlap with box
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverLapBegin);

	// If mat is valid
	if (baseMat)
	{
		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
	}

	// If mesh is valid
	if (cubeMesh)
	{
		cubeMesh->SetMaterial(0, dmiMat);
	}
	
}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeDMIMod::OnOverLapBegin(UPrimitiveComponent* OverLappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Get reference to player character
	Afirstperson415Character* overlappedActor = Cast<Afirstperson415Character>(OtherActor);

	// Generate random color
	if (overlappedActor)
	{
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);

		FVector4 randColor = FVector4(ranNumX, ranNumY, ranNumZ, 1.f);
		if (dmiMat)
		{
			dmiMat->SetVectorParameterValue("Color", randColor);
			dmiMat->SetScalarParameterValue("Darkness", ranNumX);
		}
	}
}

