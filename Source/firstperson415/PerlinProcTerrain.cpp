// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create default sub object and setup attachment
	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");
	ProcMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();

	// Call CreateVertices and CreateTriangles
	CreateVertices();
	CreateTriangles();
	// Create mesh section and set matieral
	ProcMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true);
	ProcMesh->SetMaterial(0, Mat);
	
}

// Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProcTerrain::AlterMesh(FVector impactPoint)
{
	// Check for total num of vertices
	for (int i = 0; i < Vertices.Num(); i++)
	{
		// set temp vector var to calculate dig to be whre trace actually is
		FVector tempVector = impactPoint - this->GetActorLocation();

		// If the vertice is within radius value
		if (FVector(Vertices[i] - tempVector).Size() < radius)
		{
			// Set array element of vertices in this index - depth
			Vertices[i] = Vertices[i] - Depth;
			// Update mesh section to see the dig effect
			ProcMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

void APerlinProcTerrain::CreateVertices()
{
	for (int X = 0; X <= XSize; X++)
	{
		for (int Y = 0; Y <= YSize; Y++)
		{
			// Create float and use perlin noise to generate a random scale
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;
			// Print Z value
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z %f"), Z));
			// Each vertex get x value and multiply by scale
			Vertices.Add(FVector(X * Scale, Y * Scale, Z));
			// Each UV multiply by scale
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
		}
	}
}

void APerlinProcTerrain::CreateTriangles()
{
	// Cycle through vertex values to dertimine which ones are drawn to where
	int Vertex = 0;

	for (int X = 0; X < XSize; X++)
	{
		for (int Y = 0; Y < YSize; Y++)
		{
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);

			Vertex++;
		}

		Vertex++;
	}
}

