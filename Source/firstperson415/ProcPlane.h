// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcPlane.generated.h"

class UProceduralMeshComponent;

UCLASS()
class FIRSTPERSON415_API AProcPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Array var vertices
	UPROPERTY(EditAnywhere)
		TArray<FVector> Vertices;

	// Array var triangles
	UPROPERTY(EditAnywhere)
		TArray<int> Triangles;

	// Array var UV0 for UVs
	UPROPERTY(EditAnywhere)
		TArray<FVector2D> UV0;

	// Create function
	UFUNCTION()
		void CreateMesh();

	// Declare PlaneMat var
	UPROPERTY(EditAnywhere)
		UMaterialInterface* PlaneMat;

private:
	// Declare procMesh var
	UProceduralMeshComponent* procMesh;


};
