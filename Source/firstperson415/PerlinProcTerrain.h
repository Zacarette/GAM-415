// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class FIRSTPERSON415_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

	// Vars to generate size of landscape
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int XSize = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int YSize = 0;

	// Vars to mulitiply the height of our noise
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
		float ZMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float NoiseScale = 1.0f;

	// Vars for Scale and UVScale
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float Scale = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float UVScale = 0;

	// Var for radius (how big of a hole)
	UPROPERTY(EditAnywhere)
		float radius;

	// Var for Depth (how deep of a hole)
	UPROPERTY(EditAnywhere)
		FVector Depth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Declare Mat var
	UPROPERTY(EditAnywhere)
		UMaterialInterface* Mat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to alter mesh
	UFUNCTION()
		void AlterMesh(FVector impactPoint);

private:
	UProceduralMeshComponent* ProcMesh;
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;

	int sectionID = 0;

	void CreateVertices();
	void CreateTriangles();

};
