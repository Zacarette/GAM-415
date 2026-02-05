// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "firstperson415Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create default sub objects and setup root component and attachments
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");

	RootComponent = boxComp;
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent);

	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	// On overlap with boxcomp call OnOverlapBegin function
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	mesh->SetHiddenInSceneCapture(true);
	mesh->bCastStaticShadow = false;
	mesh->bCastDynamicShadow = false;

	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Each tick call UpdatePortal functions
	UpdatePortals();

}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Afirstperson415Character* playerChar = Cast<Afirstperson415Character>(OtherActor);

	// If playerChar is valid
	if (playerChar)
	{
		// If OtherPortal is valid
		if (OtherPortal)
		{
			// If isTeleporting is false
			if (!playerChar->isTeleporting)
			{
				// Set isTeleporting to true, set vector loc to OtherPortals location, set playerChar location to loc
				playerChar->isTeleporting = true;
				FVector loc = OtherPortal->rootArrow->GetComponentLocation();
				playerChar->SetActorLocation(loc);

				// Sets isTeleporting back to false after a delay of 1 second once
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);
			}
		}
	}
}

void APortal::SetBool(Afirstperson415Character* playerChar)
{
	// Setup helper function that only sets isTeleporting to false so it can be used on line 73
	if (playerChar)
	{
		playerChar->isTeleporting = false;
	}
}

void APortal::UpdatePortals()
{
	// Set vector Location that gets the diference between this class and OtherPortal actor location
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();
	// Set vector camLocation that returns cam location
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	// Set vector camRotation that returns cam rotation
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();
	// Set vector CombinedLocation that combines cam location and this actor location
	FVector CombinedLocation = camLocation + Location;

	// Set world location and rotation of scenceCapture component
	sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);
}

